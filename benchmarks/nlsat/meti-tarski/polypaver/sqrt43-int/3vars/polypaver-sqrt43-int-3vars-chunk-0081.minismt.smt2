(set-logic QF_NRA)
(declare-fun skoEC1 () Real)
(declare-fun skoRC1 () Real)
(declare-fun skoXC1 () Real)
(assert (not (<= (+ (* (- 1) skoXC1) (* (- 3) (* skoEC1 skoXC1)) (* skoRC1 skoRC1) (* (- 3) (* skoEC1 skoEC1 skoXC1)) (* (- 2) (* skoEC1 skoRC1 skoRC1)) (* (- 1) (* skoEC1 skoEC1 skoEC1 skoXC1)) (* (- 1) (* skoEC1 skoEC1 skoRC1 skoRC1))) 0)))
(set-info :status sat)
(check-sat)