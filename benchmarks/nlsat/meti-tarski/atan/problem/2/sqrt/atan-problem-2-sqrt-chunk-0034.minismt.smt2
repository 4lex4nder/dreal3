(set-logic QF_NRA)
(declare-fun skoT () Real)
(declare-fun skoB () Real)
(declare-fun skoA () Real)
(assert (and (not (<= (+ (* 2 skoB) (* (- 2) skoA) (* skoT skoT)) 0)) (and (not (<= (+ (* (- 1) (* skoT skoT skoB)) (* skoT skoT skoA)) 0)) (and (not (<= (+ skoB (* (- 1) skoA)) 0)) (and (not (<= (* (- 1) skoB) (- 2))) (and (not (<= skoA 0)) (not (= skoT 0))))))))
(set-info :status unsat)
(check-sat)