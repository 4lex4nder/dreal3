(set-logic QF_NRA)

(declare-fun skoX () Real)
(declare-fun skoS () Real)
(declare-fun skoC () Real)
(assert (and (<= (* skoX (+ (/ 57. 500.) (* skoX (/ 361. 1000000.)))) (- 12.)) (and (not (<= skoX 0.)) (and (not (<= (* skoC (/ 1770. 689.)) skoS)) (and (<= skoS (* skoC (/ 1770. 689.))) (and (or (not (<= (* skoC (/ 1770. 689.)) skoS)) (<= skoX 0.)) (and (or (<= skoS (* skoC (/ 1770. 689.))) (<= skoX 0.)) (and (= (* skoS skoS) (+ 1. (* skoC (* skoC (- 1.))))) (and (<= skoX 289.) (<= 0. skoX))))))))))
(set-info :status unsat)
(check-sat)