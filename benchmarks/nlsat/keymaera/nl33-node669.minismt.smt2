(set-logic QF_NRA)
(set-info :source | KeYmaera example: nl33, node 66
Andre Platzer, Jan-David Quesel, and Philipp Rümmer. Real world verification. In Renate A. Schmidt, editor, International Conference on Automated Deduction, CADE'09, Montreal, Canada, Proceedings, volume 5663 of LNCS, pages 485(- 501.) Springer, 2009.
 |)
(set-info :smt-lib-version 2.0)
(declare-fun x () Real)
(declare-fun y () Real)
(declare-fun a () Real)
(assert (not (implies (and (and (not (>= (* (- 2) x) (- 3))) (not (>= (* (- 1) y) (- 1)))) (not (>= (+ (* 7 a) (* 3 (* x y))) 4))) (not (>= a 0)))))
(check-sat)
