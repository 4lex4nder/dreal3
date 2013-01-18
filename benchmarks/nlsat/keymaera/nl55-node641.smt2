(set-logic QF_NRA)
(set-info :source | KeYmaera example: nl55, node 64
Andre Platzer, Jan-David Quesel, and Philipp Rümmer. Real world verification. In Renate A. Schmidt, editor, International Conference on Automated Deduction, CADE'09, Montreal, Canada, Proceedings, volume 5663 of LNCS, pages 485(- 501.) Springer, 2009.
 |)
(set-info :smt-lib-version 2.0)
(declare-const x5 Real)
(declare-const x4 Real)
(declare-const x2 Real)
(declare-const x3 Real)
(declare-const x1 Real)
(assert (not (=> (and (and (<= x5 x4 ) (= x2 (+ x5 x3) )) (<= x4 x5 )) (= (* x2 x1) (+ (* x4 x1) (* x3 x1)) ))))
(check-sat)
