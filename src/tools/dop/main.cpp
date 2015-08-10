/*********************************************************************
Author: Soonho Kong <soonhok@cs.cmu.edu>

dReal -- Copyright (C) 2013 - 2015, Soonho Kong, Sicun Gao, and Edmund Clarke

dReal is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

dReal is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with dReal. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#include <sys/stat.h>
#include <ezOptionParser/ezOptionParser.hpp>
#include <pegtl.hh>
#include <algorithm>
#include <cassert>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "./config.h"
#include "./version.h"
#include "opensmt/api/OpenSMTContext.h"
#include "opensmt/egraph/Enode.h"
#include "tools/dop/dopconfig.h"
#include "util/subst_enode.h"
#include "tools/dop/parser.h"
#include "tools/dop/print_py.h"
#include "tools/dop/print_latex.h"
#include "tools/dop/visualize.h"
#include "util/logging.h"

using std::back_inserter;
using std::cerr;
using std::copy;
using std::endl;
using std::pair;
using std::runtime_error;
using std::sort;
using std::string;
using std::unordered_map;
using std::vector;

namespace dop {

static const char g_minimum_name[] = "min";

Enode * make_univ_ctr(OpenSMTContext & ctx, unordered_map<string, Enode *> const & m, Enode * f) {
    cerr << "make_univ_ctr = " << f << endl;
    unordered_map<Enode *, Enode *> subst_map;

    // 1. need to create a mapping from exist variables to forall variables
    Snode * const real_sort = ctx.mkSortReal();
    for (auto const & p : m) {
        string const name = p.first;
        string const forall_var_name = string("forall_") + name;
        Enode * exist_var = p.second;
        double const lb = exist_var->getDomainLowerBound();
        double const ub = exist_var->getDomainUpperBound();
        ctx.DeclareFun(forall_var_name.c_str(), real_sort);
        Enode * const forall_var = ctx.mkVar(forall_var_name.c_str(), true);
        forall_var->setForallVar();
        forall_var->setDomainLowerBound(lb);
        forall_var->setDomainUpperBound(ub);
        forall_var->setValueLowerBound(lb);
        forall_var->setValueUpperBound(ub);
        subst_map.emplace(exist_var, forall_var);
        cerr << "subst_map: "
             << exist_var << " => " << forall_var << endl;
    }
    // 2. need to make f(y1, y2) based on f(x1, x2)
    Enode * forall_f = dreal::subst(ctx, f, subst_map);
    return forall_f;
}

Enode * make_leq_cost(OpenSMTContext & ctx, unordered_map<string, Enode *> const & m, Enode * f, Enode * min_var) {
    unordered_map<Enode *, Enode *> subst_map;

    // 1. need to create a mapping from exist variables to forall variables
    Snode * const real_sort = ctx.mkSortReal();
    for (auto const & p : m) {
        string const name = p.first;
        string const forall_var_name = string("forall_") + name;
        Enode * exist_var = p.second;
        double const lb = exist_var->getDomainLowerBound();
        double const ub = exist_var->getDomainUpperBound();
        ctx.DeclareFun(forall_var_name.c_str(), real_sort);
        Enode * const forall_var = ctx.mkVar(forall_var_name.c_str(), true);
        forall_var->setForallVar();
        forall_var->setDomainLowerBound(lb);
        forall_var->setDomainUpperBound(ub);
        forall_var->setValueLowerBound(lb);
        forall_var->setValueUpperBound(ub);
        subst_map.emplace(exist_var, forall_var);
    }

    // opensmt_expr formula = opensmt_mk_forall(ctx, vars, 1,
    //                                          opensmt_mk_or_2(ctx, circle1, circle2));


    // 2. need to make f(y1, y2) based on f(x1, x2)
    Enode * forall_f = dreal::subst(ctx, f, subst_map);

    // 3. return f(x1, x2) <= f(y1, y2) /\ min* = f(x1, x2)
    Enode * const args_list = ctx.mkCons(min_var, ctx.mkCons(forall_f));
    Enode * const leq = ctx.mkLeq(args_list);
    return leq;
}

Enode * make_min_var(OpenSMTContext & ctx, unordered_map<string, Enode *> & m) {
    Snode * const real_sort = ctx.mkSortReal();
    ctx.DeclareFun(g_minimum_name, real_sort);
    Enode * const min_var = ctx.mkVar(g_minimum_name, true);
    m.emplace(g_minimum_name, min_var);
    return min_var;
}

Enode * make_eq_cost(OpenSMTContext & ctx, Enode * e1, Enode * e2) {
    Enode * const eq = ctx.mkEq(ctx.mkCons(e1, ctx.mkCons(e2)));
    return eq;
}

ostream & display(ostream & out, string const & name, Enode * const e) {
    out << name << " = "
        << "[" << e->getValueLowerBound() << ", "
        << e->getValueUpperBound() << "]";
    return out;
}

void print_result(unordered_map<string, Enode*> const & map) {
    vector<pair<string, Enode*>> vec;
    copy(map.begin(), map.end(), back_inserter(vec));
    sort(vec.begin(), vec.end(), [](pair<string, Enode *> const & p1, pair<string, Enode *> const & p2) {
            if (p1.first == g_minimum_name) {
                return false;
            } else if (p2.first == g_minimum_name) {
                return true;
            } else {
                return p1.first < p2.first;
            }
        });
    for (auto const item : vec) {
        string name = item.first;
        Enode * e = item.second;
        cout << "\t"; dop::display(cout, name, e) << endl;
    }
}
}  // namespace dop

int main(int argc, const char * argv[]) {
#ifdef LOGGING
    START_EASYLOGGINGPP(argc, argv);
#endif
    dop::config config(argc, argv);
    string const filename = config.get_filename();
    pegtl::read_parser parser { filename };
    dop::pstate p;
    try {
        parser.parse<dop::grammar, dop::action, dop::control>(p);
    } catch (pegtl::parse_error const & e) {
        throw runtime_error(e.what());
    }
    OpenSMTContext & ctx = p.get_ctx();
    unordered_map<string, Enode *> var_map = p.get_var_map();
    Enode * const cost = p.get_cost();
    Enode * const ctr = p.get_ctr();
    double const prec = config.get_precision() > 0 ? config.get_precision() : p.get_precision();
    ctx.setPrecision(prec);
    Enode * min_var = dop::make_min_var(ctx, var_map);
    Enode * ctr_y = dop::make_univ_ctr(ctx, var_map, ctr);               // ctr(y)
    Enode * eq_cost = dop::make_eq_cost(ctx, cost, min_var);             // cost(x) = min
    Enode * leq_cost = dop::make_leq_cost(ctx, var_map, cost, min_var);  // min <= cost(y)
    Enode * term = ctx.mkOr(ctx.mkCons(ctx.mkNot(ctx.mkCons(ctr_y)), ctx.mkCons(leq_cost)));  // !ctr(y) \/ (min <= cost(y))

    vector<pair<string, Snode *>*> sorted_var_list;
    for (Enode * e : term->get_forall_vars()) {
        std::pair<string, Snode *> * p = new std::pair<string, Snode *>(e->getCar()->getName(), e->getSort());
        sorted_var_list.push_back(p);
    }
    Enode * quantified = ctx.mkForall(&sorted_var_list, term);
    cerr << "term = " << term << endl;
    cerr << "quantified = " << quantified << endl;
    ctx.Assert(eq_cost);
    ctx.Assert(ctr);
    // ctx.Assert(leq_cost);
    ctx.Assert(quantified);
    cout << "Minimize   : " << cost << endl;
    cout << "Constraint : " << ctr << endl;
    cout << "Precision  : " << prec << endl;
    cout << "Solve      : " << leq_cost << endl
         << "             " << eq_cost << endl
         << "             " << ctr << endl
         << "             " << ctr_y << endl;
    cout << "Result     : ";
    if (ctx.CheckSAT() == l_True) {
        cout << "delta-sat" << endl;
        dop::print_result(var_map);
        if (config.get_visualize()) {
            dop::visualize_result_via_python(cost, var_map, config.get_vis_cell(), dop::g_minimum_name);
        }
    } else {
        cout << "unsat" << endl;
    }
    return 0;
}
// minimize cost(x)
// satisfying ctr(x)
// exists x. ctr(x) /\ forall y. [ctr(y) -> (cost(x) <= cost(y))]
// exists x. ctr(x) /\ forall y. [!ctr(y) \/ (cost(x) <= cost(y))]
// exists x, min. cost(x) = min /\
//                ctr(x) /\
//                forall y. [!ctr(y) \/ min <= cost(y))]
