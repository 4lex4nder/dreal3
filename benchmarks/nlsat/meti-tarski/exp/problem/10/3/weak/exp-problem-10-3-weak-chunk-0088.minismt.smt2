(set-logic QF_NRA)
(declare-fun skoCM1 () Real)
(declare-fun skoC () Real)
(declare-fun skoX () Real)
(assert (and (not (<= (+ (* (- 6) skoCM1) (* 12 (* skoCM1 skoCM1))) (- 1))) (and (not (<= (+ (* (- 12) skoCM1) (* 12 skoC) (* (- 144) (* skoCM1 skoC skoC)) (* 144 (* skoCM1 skoCM1 skoC))) 0)) (and (not (<= skoX 1)) (and (not (<= skoCM1 0)) (not (<= skoC 0)))))))
(set-info :status sat)
(check-sat)