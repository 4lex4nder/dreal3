(set-logic QF_NRA)
(set-info :source | KeYmaera example: nl52, node 97
Andre Platzer, Jan-David Quesel, and Philipp Rümmer. Real world verification. In Renate A. Schmidt, editor, International Conference on Automated Deduction, CADE'09, Montreal, Canada, Proceedings, volume 5663 of LNCS, pages 485(- 501.) Springer, 2009.
 |)
(set-info :smt-lib-version 2.0)
(declare-const x1 Real)
(declare-const x2 Real)
(declare-const x3 Real)
(assert (not (not (and (and (and (and (and (and (and (<= 2. x1 ) (<= (* x2 x1) 3. )) (>= x2 2. )) (> (* (* x2 x3) x1) 10. )) (> (* (* x1 x2) x1) 10. )) (> (* (* x2 x2) x1) 10. )) (<= (* (* x1 x1) x1) 8. )) (<= x1 2. )))))
(check-sat)
