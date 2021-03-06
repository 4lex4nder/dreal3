/*********************************************************************
Author: Roberto Bruttomesso <roberto.bruttomesso@gmail.com>

OpenSMT -- Copyright (C) 2009, Roberto Bruttomesso

OpenSMT is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenSMT is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenSMT. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#include "tsolvers/THandler.h"
#include "smtsolvers/CoreSMTSolver.h"
#include <sys/wait.h>
#include "util/logging.h"

//
// Return the MiniSAT Variable corresponding to
// the positive input enode. Creates the correspondence
// by adding a new MiniSAT variable, if it doesn't exists
//
Var THandler::enodeToVar( Enode * atm )
{
  assert( atm );
  assert( atm->isAtom( ) );
  assert( !atm->isTrue( ) );
  assert( !atm->isFalse( ) );

  if ( enode_id_to_var.size( ) <= (unsigned)atm->getId( ) )
    enode_id_to_var.resize( atm->getId( ) + 1, var_Undef );

  Var v = enode_id_to_var[ atm->getId( ) ];




  if ( v == var_Undef )
  {
    lbool state = l_Undef;

    // Store TAtom and give later
    if ( atm->isTAtom( ) )
    {
      // Give to theory solvers right away
      if ( config.incremental )
        core_solver.inform( atm );
      // Accumulate and give to theory solvers later
      else
      {
        if ( static_cast< int >( tatoms_seen.size( ) ) <= atm->getId( ) )
          tatoms_seen.resize( atm->getId( ) + 1, false );
        if ( tatoms_seen[ atm->getId( ) ] == false )
        {
          tatoms_seen[ atm->getId( ) ] = true;
          tatoms_list.push_back( atm );
          tatoms_give.push_back( true );
        }
      }
    }

    if ( state == l_Undef )
    {
      // There is no variable in MiniSAT for this enode
      // Create a new variable and store the correspondence

      // Assign custom polarity if any
      if ( atm->isTAtom( ) && atm->getDecPolarity( ) != l_Undef )
        v = solver.newVar( atm->getDecPolarity( ) == l_False );
      else
      {
        if ( config.sat_polarity_mode == 3 )
          v = solver.newVar( false ); // Positive polarity
        else if ( config.sat_polarity_mode == 4 )
          v = solver.newVar( true );  // Negative polarity
        else
        {
          assert( (config.sat_polarity_mode == 5 && !atm->isTAtom( ))
               || (0 <= config.sat_polarity_mode && config.sat_polarity_mode <= 2 ) );
          double random_seed = 91648253;
          v = solver.newVar( irand( random_seed, 2 ) );
        }
      }

      if ( atm->isTAtom( ) )
      {
        solver.setFrozen( v, true );
        tatoms ++;
      }
      else {
        solver.setFrozen( v, true );
        batoms ++;
      }

      enode_id_to_var[ atm->getId( ) ] = v;

      if ( var_to_enode.size( ) <= (unsigned)v )
        var_to_enode.resize( v + 1, NULL );

      assert( var_to_enode[ v ] == NULL );
      var_to_enode[ v ] = atm;
    }
    else if ( state == l_False )
    {
      v = var_False;
    }
    else
    {
      v = var_True;
    }
  }

  assert( v != var_Undef );
  return v;
}

//
// Return the MiniSAT literal corresponding to
// the input enode literal. Creates the correspondence
// by adding a new MiniSAT variable, if it doesn't exists
//
Lit THandler::enodeToLit( Enode * elit )
{
  assert( elit );
  assert( elit->isLit( ) );

  bool negated = elit->isNot( );
  Enode * atm = negated ? elit->getCdr( )->getCar( ) : elit;
  Var v = enodeToVar( atm );
  return Lit( v, negated );
}

Enode * THandler::varToEnode( Var v )
{
  assert( v < (int)var_to_enode.size( ) );
  assert( var_to_enode[ v ] != NULL );
  return var_to_enode[ v ];
}

void THandler::clearVar( Var v )
{
  assert( var_to_enode[ v ] != NULL );
  Enode * e = var_to_enode[ v ];
  assert( e->getId( ) < static_cast< int >( enode_id_to_var.size( ) ) );
  assert( enode_id_to_var[ e->getId( ) ] == v );
  var_to_enode[ v ] = NULL;
  enode_id_to_var[ e->getId( ) ] = var_Undef;
}

bool THandler::assertLits( )
{
  bool res = true;

  assert( checked_trail_size == stack.size( ) );
  assert( (int)stack.size( ) <= trail.size( ) );
  DREAL_LOG_DEBUG << "THandler::assertLits() " << checked_trail_size << " " << trail.size() << endl;

  for ( int i = checked_trail_size ; i < trail.size( ) && res ; i ++ )
  {
    const Lit l = trail[ i ];
    const Var v = var( l );

    Enode * e = var_to_enode[ v ];
    assert( v <= 1 || e );
    stack.push_back( e );

    if ( v == var_True || v == var_False )
    {
      assert( v != var_True  || sign( l ) == false );
      assert( v != var_False || sign( l ) == true );
      continue;
    }

    if ( !e->isTAtom( ) )
      continue;

    // Push backtrack point
    core_solver.pushBacktrackPoint( );

    assert( !e->hasPolarity( ) );
    DREAL_LOG_DEBUG << "THandler::assertLits(): asserting " << e << " with sign = " << sign(l) << endl;
    e->setPolarity( (sign( l ) ? l_False : l_True) );
    assert( e->hasPolarity( ) );
    res = core_solver.assertLit( e );

    if ( !res && config.certification_level > 2 )
      verifyCallWithExternalTool( res, i );
  }

  checked_trail_size = stack.size( );
  assert( !res || trail.size( ) == (int)stack.size( ) );

  return res;
}

bool THandler::check( bool complete )
{
  const bool res = core_solver.check( complete );

  if ( complete && config.certification_level > 2 )
    verifyCallWithExternalTool( res, trail.size( ) - 1 );

  return res;
}

void THandler::backtrack( )
{
  // Undoes the state of theory atoms if needed
  while ( (int)stack.size( ) > trail.size( ) )
  {
    Enode * e = stack.back( );
    stack.pop_back( );

    // It was var_True or var_False
    if ( e == NULL )
      continue;

    if ( !e->isTAtom( ) )
      continue;

    core_solver.popBacktrackPoint( );

    assert( e->isTAtom( ) );
    assert( e->hasPolarity( ) );
    assert( e->getPolarity( ) == l_True
         || e->getPolarity( ) == l_False );
    // Reset polarity
    e->resetPolarity( );
    assert( !e->hasPolarity( ) );
  }
  checked_trail_size = stack.size( );
}

//
// Return the conflict generated by a theory solver
//
void THandler::getConflict ( vec< Lit > & conflict, int & max_decision_level )
{
  // First of all, the explanation in a tsolver is
  // stored as conjunction of enodes e1,...,en
  // with associated polarities p1,...,pn. Since the sat-solver
  // wants a clause we store it in the form ( l1 | ... | ln )
  // where li is the literal corresponding with ei with polarity !pi
  vector< Enode * > & explanation = core_solver.getConflict( );
  assert( !explanation.empty( ) );

  if ( config.certification_level > 0 )
    verifyExplanationWithExternalTool( explanation );

#ifdef PRODUCE_PROOF
  max_decision_level = -1;
  for ( vector< Enode * >::iterator it = explanation.begin( )
      ; it != explanation.end( )
      ; ++ it )
  {
    Enode * ei  = *it;
    assert( ei->hasPolarity( ) );
    assert( ei->getPolarity( ) == l_True
         || ei->getPolarity( ) == l_False );
    bool negate = ei->getPolarity( ) == l_False;

    Var v = enodeToVar( ei );
#if PEDANTIC_DEBUG
    assert( isOnTrail( Lit( v, negate ) ) );
#endif
    Lit l = Lit( v, !negate );
    conflict.push( l );

    if ( max_decision_level < level[ v ] )
      max_decision_level = level[ v ];
  }
  if ( config.produce_inter == 0 )
    explanation.clear( );
#else
  max_decision_level = -1;
  while ( !explanation.empty( ) )
  {
    Enode * ei  = explanation.back( );
    explanation.pop_back( );
    assert( ei->hasPolarity( ) );
    assert( ei->getPolarity( ) == l_True
         || ei->getPolarity( ) == l_False );
    bool negate = ei->getPolarity( ) == l_False;

    Var v = enodeToVar( ei );
#if PEDANTIC_DEBUG
    assert( isOnTrail( Lit( v, negate ) ) );
#endif
    Lit l = Lit( v, !negate );
    conflict.push( l );

    if ( max_decision_level < level[ v ] )
      max_decision_level = level[ v ];
  }
#endif
}

#ifdef PRODUCE_PROOF
Enode * THandler::getInterpolants( )
{
  vector< Enode * > & explanation = core_solver.getConflict( );

  assert( !explanation.empty( ) );
  Enode * interp_list = core_solver.getInterpolants( );

  // Check interpolants correctness
  if ( config.proof_certify_inter > 1 )
    verifyInterpolantWithExternalTool( explanation, interp_list );

  // Flush explanation
  explanation.clear( );

  return interp_list;
}
#endif

Lit THandler::getDeduction( )
{
  Enode * e = core_solver.getDeduction( );

  if ( e == NULL )
    return lit_Undef;

  if ( config.certification_level > 1 )
    verifyDeductionWithExternalTool( e );

  assert( e->isDeduced( ) );
  assert( e->getDeduced( ) == l_False
       || e->getDeduced( ) == l_True );
  bool negate = e->getDeduced( ) == l_False;
  Var v = enodeToVar( e );
  return Lit( v, negate );
}

Lit THandler::getSuggestion( )
{
  Enode * e = core_solver.getSuggestion( );

  if ( e == NULL )
    return lit_Undef;

  bool negate = e->getDecPolarity( ) == l_False;
  Var v = enodeToVar( e );
  return Lit( v, negate );
}

void THandler::getReason( Lit l, vec< Lit > & reason )
{
#if LAZY_COMMUNICATION
  assert( checked_trail_size == stack.size( ) );
  assert( static_cast< int >( checked_trail_size ) == trail.size( ) );
#else
#endif

  Var v = var(l);
  Enode * e = varToEnode( v );

  // It must be a TAtom and already disabled
  assert( e->isTAtom( ) );
  assert( !e->hasPolarity( ) );
  assert( e->isDeduced( ) );
  assert( e->getDeduced( ) != l_Undef );           // Last assigned deduction
#if LAZY_COMMUNICATION
  assert( e->getPolarity( ) != l_Undef );          // Last assigned polarity
  assert( e->getPolarity( ) == e->getDeduced( ) ); // The two coincide
#else
#endif

  core_solver.pushBacktrackPoint( );

  // Assign reversed polarity temporairly
  e->setPolarity( e->getDeduced( ) == l_True ? l_False : l_True );
  // Compute reason in whatever solver
  const bool res = core_solver.assertLit( e, true ) &&
                   core_solver.check( true );
  // Result must be false
  if ( res )
  {
    cout << endl << "unknown" << endl;
    exit( 1 );
  }

  // Get Explanation
  vector< Enode * > & explanation = core_solver.getConflict( true );

  if ( config.certification_level > 0 )
    verifyExplanationWithExternalTool( explanation );

  // Reserve room for implied lit
  reason.push( lit_Undef );
  // Copy explanation

  while ( !explanation.empty( ) )
  {
    Enode * ei  = explanation.back( );
    explanation.pop_back( );
    assert( ei->hasPolarity( ) );
    assert( ei->getPolarity( ) == l_True
         || ei->getPolarity( ) == l_False );
    bool negate = ei->getPolarity( ) == l_False;
    Var v = enodeToVar( ei );

    // Toggle polarity for deduced literal
    if ( e == ei )
    {
      assert( e->getDeduced( ) != l_Undef );           // But still holds the deduced polarity
      // The deduced literal must have been pushed
      // with the the same polarity that has been deduced
      reason[ 0 ] = Lit( v, !negate );
    }
    else
    {
      assert( ei->hasPolarity( ) );                    // Lit in explanation is active
      // This assertion might fail if in your theory solver
      // you do not skip deduced literals during assertLit
      //
      // TODO: check ! It could be deduced: by another solver
      // For instance BV found conflict and ei was deduced by EUF solver
      //
      // assert( !ei->isDeduced( ) );                     // and not deduced
      Lit l = Lit( v, !negate );
      reason.push( l );
    }
  }

  core_solver.popBacktrackPoint( );

  // Resetting polarity
  e->resetPolarity( );
}

//
// Inform Theory-Solvers of Theory-Atoms
//
void THandler::inform( )
{
  for ( ; tatoms_given < tatoms_list.size( ) ; tatoms_given ++ )
  {
    if ( !tatoms_give[ tatoms_given ] ) continue;
    Enode * atm = tatoms_list[ tatoms_given ];
    assert( atm );
    assert( atm->isTAtom( ) );
    core_solver.inform( atm );
  }
}

#ifdef PEDANTIC_DEBUG
bool THandler::isOnTrail( Lit l )
{
  for ( int i = 0 ; i < trail.size( ) ; i ++ )
    if ( trail[ i ] == l ) return true;

  return false;
}
#endif

void THandler::verifyCallWithExternalTool( bool res, size_t trail_size )
{
  // First stage: print declarations
  const char * name = "/tmp/verifycall.smt2";
  std::ofstream dump_out( name );

  core_solver.dumpHeaderToFile( dump_out );

  dump_out << "(assert" << endl;
  dump_out << "(and" << endl;
  for ( size_t j = 0 ; j <= trail_size ; j ++ )
  {
    Var v = var( trail[ j ] );

    if ( v == var_True || v == var_False )
      continue;

    // Enode * e = var_to_enode[ v ];
    Enode * e = varToEnode( v );
    assert( e );

    if ( !e->isTAtom( ) )
      continue;

    bool negated = sign( trail[ j ] );
    if ( negated )
      dump_out << "(not ";
    e->print( dump_out );
    if ( negated )
      dump_out << ")";

    dump_out << endl;
  }
  dump_out << "))" << endl;
  dump_out << "(check-sat)" << endl;
  dump_out << "(exit)" << endl;
  dump_out.close( );

  // Second stage, check the formula
  const bool tool_res = callCertifyingSolver( name );

  if ( res == false && tool_res == true )
    opensmt_error2( config.certifying_solver, " says SAT stack, but we say UNSAT" );

  if ( res == true && tool_res == false )
    opensmt_error2( config.certifying_solver, " says UNSAT stack, but we say SAT" );
}

void THandler::verifyExplanationWithExternalTool( vector< Enode * > & expl )
{
  // First stage: print declarations
  const char * name = "/tmp/verifyexp.smt2";
  std::ofstream dump_out( name );

  core_solver.dumpHeaderToFile( dump_out );

  dump_out << "(assert " << endl;
  dump_out << "(and" << endl;

  for ( size_t j = 0 ; j < expl.size( ) ; j ++ )
  {
    Enode * e = expl[ j ];
    assert( e->isTAtom( ) );
    assert( e->getPolarity( ) != l_Undef );
    bool negated = e->getPolarity( ) == l_False;
    if ( negated )
      dump_out << "(not ";
    e->print( dump_out );
    if ( negated )
      dump_out << ")";

    dump_out << endl;
  }

  dump_out << "))" << endl;
  dump_out << "(check-sat)" << endl;
  dump_out << "(exit)" << endl;
  dump_out.close( );
  // Third stage, check the formula
  const bool tool_res = callCertifyingSolver( name );

  if ( tool_res == true )
    opensmt_error2( config.certifying_solver, " says this is not an explanation" );
}

void THandler::verifyDeductionWithExternalTool( Enode * imp )
{
  assert( imp->isDeduced( ) );

  // First stage: print declarations
  const char * name = "/tmp/verifydeduction.smt2";
  std::ofstream dump_out( name );

  core_solver.dumpHeaderToFile( dump_out );

  dump_out << "(assert" << endl;
  dump_out << "(and" << endl;
  for ( int j = 0 ; j < trail.size( ) ; j ++ )
  {
    Var v = var( trail[ j ] );

    if ( v == var_True || v == var_False )
      continue;

    Enode * e = varToEnode( v );
    assert( e );

    if ( !e->isTAtom( ) )
      continue;

    bool negated = sign( trail[ j ] );
    if ( negated )
      dump_out << "(not ";
    e->print( dump_out );
    if ( negated )
      dump_out << ")";

    dump_out << endl;
  }

  if ( imp->getDeduced( ) == l_True )
    dump_out << "(not " << imp << ")" << endl;
  else
    dump_out << imp << endl;

  dump_out << "))" << endl;
  dump_out << "(check-sat)" << endl;
  dump_out << "(exit)" << endl;
  dump_out.close( );

  // Second stage, check the formula
  const bool tool_res = callCertifyingSolver( name );

  if ( tool_res )
    opensmt_error2( config.certifying_solver, " says this is not a valid deduction" );
}

bool THandler::callCertifyingSolver( const char * name )
{
  bool tool_res;
  if ( int pid = fork() )
  {
    int status;
    waitpid(pid, &status, 0);
    switch ( WEXITSTATUS( status ) )
    {
      case 0:
        tool_res = false;
        break;
      case 1:
        tool_res = true;
        break;
      default:
        perror( "# Error: Certifying solver returned weird answer (should be 0 or 1)" );
        exit( EXIT_FAILURE );
    }
  }
  else
  {
    execlp( config.certifying_solver
          , config.certifying_solver
          , name
          , NULL );
    perror( "# Error: Cerifying solver had some problems (check that it is reachable and executable)" );
    exit( EXIT_FAILURE );
  }
  return tool_res;
}

#ifdef PRODUCE_PROOF
void THandler::verifyInterpolantWithExternalTool( vector< Enode * > & expl
                                                , Enode * interp_list )
{
  uint64_t mask = 0xFFFFFFFFFFFFFFFEULL;
  for ( unsigned in = 1 ; in < core_solver.getNofPartitions( ) ; in ++ )
  {
    Enode * args = interp_list;
    // Advance in the interpolants list
    for ( unsigned i = 0 ; i < in - 1 ; i ++ )
      args = args->getCdr( );
    Enode * interp = args->getCar( );
    mask &= ~SETBIT( in );
    // Check A -> I, i.e., A & !I
    // First stage: print declarations
    const char * name = "/tmp/verifyinterp.smt2";
    std::ofstream dump_out( name );
    core_solver.dumpHeaderToFile( dump_out );
    // Print only A atoms
    dump_out << "(assert " << endl;
    dump_out << "(and" << endl;
    for ( size_t j = 0 ; j < expl.size( ) ; j ++ )
    {
      Enode * e = expl[ j ];
      assert( e->isTAtom( ) );
      assert( e->getPolarity( ) != l_Undef );
      assert( (core_solver.getIPartitions( e ) &  mask) != 0
           || (core_solver.getIPartitions( e ) & ~mask) != 0 );
      if ( (core_solver.getIPartitions( e ) & ~mask) != 0 )
      {
        bool negated = e->getPolarity( ) == l_False;
        if ( negated )
          dump_out << "(not ";
        e->print( dump_out );
        if ( negated )
          dump_out << ")";
        dump_out << endl;
      }
    }

    dump_out << "(not " << interp << ")" << endl;
    dump_out << "))" << endl;
    dump_out << "(check-sat)" << endl;
    dump_out << "(exit)" << endl;
    dump_out.close( );
    // Check !
    bool tool_res;
    if ( int pid = fork() )
    {
      int status;
      waitpid(pid, &status, 0);
      switch ( WEXITSTATUS( status ) )
      {
        case 0:
          tool_res = false;
          break;
        case 1:
          tool_res = true;
          break;
        default:
          perror( "Tool" );
          exit( EXIT_FAILURE );
      }
    }
    else
    {
      execlp( "tool_wrapper.sh", "tool_wrapper.sh", name, 0 );
      perror( "Tool" );
      exit( 1 );
    }

    if ( tool_res == true )
      opensmt_error2( config.certifying_solver, " says A -> I does not hold" );
    // Now check B & I
    dump_out.open( name );
    core_solver.dumpHeaderToFile( dump_out );
    // Print only B atoms
    dump_out << "(assert " << endl;
    dump_out << "(and" << endl;
    for ( size_t j = 0 ; j < expl.size( ) ; j ++ )
    {
      Enode * e = expl[ j ];
      assert( e->isTAtom( ) );
      assert( e->getPolarity( ) != l_Undef );
      assert( (core_solver.getIPartitions( e ) &  mask) != 0
           || (core_solver.getIPartitions( e ) & ~mask) != 0 );
      if ( (core_solver.getIPartitions( e ) & mask) != 0 )
      {
        bool negated = e->getPolarity( ) == l_False;
        if ( negated )
          dump_out << "(not ";
        e->print( dump_out );
        if ( negated )
          dump_out << ")";
        dump_out << endl;
      }
    }
    dump_out << interp << endl;
    dump_out << "))" << endl;
    dump_out << "(check-sat)" << endl;
    dump_out << "(exit)" << endl;
    dump_out.close( );
    // Check !
    tool_res;
    if ( int pid = fork() )
    {
      int status;
      waitpid(pid, &status, 0);
      switch ( WEXITSTATUS( status ) )
      {
        case 0:
          tool_res = false;
          break;
        case 1:
          tool_res = true;
          break;
        default:
          perror( "Tool" );
          exit( EXIT_FAILURE );
      }
    }
    else
    {
      execlp( "tool_wrapper.sh", "tool_wrapper.sh", name, 0 );
      perror( "Tool" );
      exit( 1 );
    }
    if ( tool_res == true )
      opensmt_error2( config.certifying_solver, " says B & I does not hold" );
  }
}
#endif
