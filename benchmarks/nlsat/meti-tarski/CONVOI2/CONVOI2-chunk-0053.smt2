(set-logic QF_NRA)

(declare-fun skoT () Real)
(declare-fun skoVF () Real)
(declare-fun skoS () Real)
(declare-fun skoC () Real)
(assert (and (not (<= (* skoVF (+ (+ (* skoC (/ 939. 250.)) (* skoS (/ 201. 6250.))) (* skoT (+ (+ (* skoC (/ 149301. 250000.)) (* skoS (/ 31959. 6250000.))) (* skoT (+ (* skoC (/ 7912953. 250000000.)) (* skoS (/ 1693827. 6250000000.)))))))) (+ (+ (* skoC (/ (- 939.) 50.)) (* skoS (/ (- 201.) 1250.))) (* skoT (+ (+ (* skoC (/ (- 149301.) 50000.)) (* skoS (/ (- 31959.) 1250000.))) (* skoT (+ (* skoC (/ (- 7912953.) 50000000.)) (* skoS (/ (- 1693827.) 1250000000.))))))))) (and (not (<= (* skoVF (+ (+ (+ (/ (- 1116.) 25.) (* skoC (/ 5634. 125.))) (* skoS (/ 1206. 3125.))) (* skoT (+ (+ (+ (/ 143631. 6250.) (* skoC (/ (- 1439487.) 62500.))) (* skoS (/ (- 308133.) 1562500.))) (* skoT (+ (+ (+ (/ 177377037. 6250000.) (* skoC (/ 145160949. 62500000.))) (* skoS (/ 31072791. 1562500000.))) (* skoT (+ (+ (+ (/ 4788768519. 625000000.) (* skoC (/ 5111618337. 6250000000.))) (* skoS (/ 1094180283. 156250000000.))) (* skoT (+ (+ (/ (- 3518078679.) 62500000000.) (* skoC (/ 35521246017. 625000000000.))) (* skoS (/ 7603589403. 15625000000000.)))))))))))) (+ (+ (+ (/ (- 2484.) 5.) (* skoC (/ (- 5634.) 25.))) (* skoS (/ (- 1206.) 625.))) (* skoT (+ (+ (+ (/ (- 889731.) 1250.) (* skoC (/ 1439487. 12500.))) (* skoS (/ 308133. 312500.))) (* skoT (+ (+ (+ (/ (- 415508337.) 1250000.) (* skoC (/ (- 145160949.) 12500000.))) (* skoS (/ (- 31072791.) 312500000.))) (* skoT (+ (+ (+ (/ (- 7438169619.) 125000000.) (* skoC (/ (- 5111618337.) 1250000000.))) (* skoS (/ (- 1094180283.) 31250000000.))) (* skoT (+ (+ (/ (- 7830562221.) 12500000000.) (* skoC (/ (- 35521246017.) 125000000000.))) (* skoS (/ (- 7603589403.) 3125000000000.))))))))))))) (and (not (<= skoVF 0.)) (and (not (<= skoT 0.)) (not (<= (/ 151. 50.) skoVF)))))))
(set-info :status sat)
(check-sat)