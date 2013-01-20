(set-logic QF_NRA)
(declare-fun c2uscore2dollarsk!17 () Real)
(declare-fun x2uscore4dollarsk!8 () Real)
(declare-fun omuscore3dollarsk!16 () Real)
(declare-fun d1uscore4dollarsk!10 () Real)
(declare-fun c1uscore2dollarsk!18 () Real)
(declare-fun x1uscore4dollarsk!9 () Real)
(declare-fun d2uscore4dollarsk!11 () Real)
(declare-fun y2uscore4dollarsk!4 () Real)
(declare-fun e1uscore4dollarsk!6 () Real)
(declare-fun y1uscore4dollarsk!5 () Real)
(declare-fun e2uscore4dollarsk!7 () Real)
(declare-fun z2uscore4dollarsk!0 () Real)
(declare-fun f1uscore4dollarsk!2 () Real)
(declare-fun z1uscore4dollarsk!1 () Real)
(declare-fun f2uscore4dollarsk!3 () Real)
(declare-fun u2uscore4dollarsk!12 () Real)
(declare-fun g1uscore4dollarsk!14 () Real)
(declare-fun u1uscore4dollarsk!13 () Real)
(declare-fun g2uscore4dollarsk!15 () Real)
(declare-fun protectedzone () Real)
(declare-fun y2uscore3dollarsk!23 () Real)
(declare-fun x2uscore3dollarsk!25 () Real)
(declare-fun y1uscore3dollarsk!24 () Real)
(declare-fun x1uscore3dollarsk!26 () Real)
(declare-fun z2uscore3dollarsk!21 () Real)
(declare-fun z1uscore3dollarsk!22 () Real)
(declare-fun u2uscore3dollarsk!19 () Real)
(declare-fun u1uscore3dollarsk!20 () Real)
(declare-fun y2uscore2dollarsk!34 () Real)
(declare-fun x2uscore2dollarsk!32 () Real)
(declare-fun y1uscore2dollarsk!33 () Real)
(declare-fun x1uscore2dollarsk!31 () Real)
(declare-fun z2uscore2dollarsk!30 () Real)
(declare-fun z1uscore2dollarsk!29 () Real)
(declare-fun u2uscore2dollarsk!28 () Real)
(declare-fun u1uscore2dollarsk!27 () Real)
(declare-fun y2 () Real)
(declare-fun x2 () Real)
(declare-fun y1 () Real)
(declare-fun x1 () Real)
(declare-fun z2 () Real)
(declare-fun z1 () Real)
(declare-fun u2 () Real)
(declare-fun u1 () Real)
(assert (= d1uscore4dollarsk!10
           (* (- 1.0)
              omuscore3dollarsk!16
              (+ x2uscore4dollarsk!8 (* (- 1.0) c2uscore2dollarsk!17)))))
(assert (= d2uscore4dollarsk!11
           (* omuscore3dollarsk!16
              (+ x1uscore4dollarsk!9 (* (- 1.0) c1uscore2dollarsk!18)))))
(assert (= e1uscore4dollarsk!6
           (* (- 1.0)
              omuscore3dollarsk!16
              (+ y2uscore4dollarsk!4 (* (- 1.0) c2uscore2dollarsk!17)))))
(assert (= e2uscore4dollarsk!7
           (* omuscore3dollarsk!16
              (+ y1uscore4dollarsk!5 (* (- 1.0) c1uscore2dollarsk!18)))))
(assert (= f1uscore4dollarsk!2
           (* (- 1.0)
              omuscore3dollarsk!16
              (+ z2uscore4dollarsk!0 (* (- 1.0) c2uscore2dollarsk!17)))))
(assert (= f2uscore4dollarsk!3
           (* omuscore3dollarsk!16
              (+ z1uscore4dollarsk!1 (* (- 1.0) c1uscore2dollarsk!18)))))
(assert (= g1uscore4dollarsk!14
           (* (- 1.0)
              omuscore3dollarsk!16
              (+ u2uscore4dollarsk!12 (* (- 1.0) c2uscore2dollarsk!17)))))
(assert (= g2uscore4dollarsk!15
           (* omuscore3dollarsk!16
              (+ u1uscore4dollarsk!13 (* (- 1.0) c1uscore2dollarsk!18)))))
(assert (>= (+ (* (+ x1uscore3dollarsk!26 (* (- 1.0) y1uscore3dollarsk!24))
                  (+ x1uscore3dollarsk!26 (* (- 1.0) y1uscore3dollarsk!24)))
               (* (+ x2uscore3dollarsk!25 (* (- 1.0) y2uscore3dollarsk!23))
                  (+ x2uscore3dollarsk!25 (* (- 1.0) y2uscore3dollarsk!23))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ y1uscore3dollarsk!24 (* (- 1.0) z1uscore3dollarsk!22))
                  (+ y1uscore3dollarsk!24 (* (- 1.0) z1uscore3dollarsk!22)))
               (* (+ y2uscore3dollarsk!23 (* (- 1.0) z2uscore3dollarsk!21))
                  (+ y2uscore3dollarsk!23 (* (- 1.0) z2uscore3dollarsk!21))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ x1uscore3dollarsk!26 (* (- 1.0) z1uscore3dollarsk!22))
                  (+ x1uscore3dollarsk!26 (* (- 1.0) z1uscore3dollarsk!22)))
               (* (+ x2uscore3dollarsk!25 (* (- 1.0) z2uscore3dollarsk!21))
                  (+ x2uscore3dollarsk!25 (* (- 1.0) z2uscore3dollarsk!21))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ x1uscore3dollarsk!26 (* (- 1.0) u1uscore3dollarsk!20))
                  (+ x1uscore3dollarsk!26 (* (- 1.0) u1uscore3dollarsk!20)))
               (* (+ x2uscore3dollarsk!25 (* (- 1.0) u2uscore3dollarsk!19))
                  (+ x2uscore3dollarsk!25 (* (- 1.0) u2uscore3dollarsk!19))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ y1uscore3dollarsk!24 (* (- 1.0) u1uscore3dollarsk!20))
                  (+ y1uscore3dollarsk!24 (* (- 1.0) u1uscore3dollarsk!20)))
               (* (+ y2uscore3dollarsk!23 (* (- 1.0) u2uscore3dollarsk!19))
                  (+ y2uscore3dollarsk!23 (* (- 1.0) u2uscore3dollarsk!19))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ z1uscore3dollarsk!22 (* (- 1.0) u1uscore3dollarsk!20))
                  (+ z1uscore3dollarsk!22 (* (- 1.0) u1uscore3dollarsk!20)))
               (* (+ z2uscore3dollarsk!21 (* (- 1.0) u2uscore3dollarsk!19))
                  (+ z2uscore3dollarsk!21 (* (- 1.0) u2uscore3dollarsk!19))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ x1uscore2dollarsk!31 (* (- 1.0) y1uscore2dollarsk!33))
                  (+ x1uscore2dollarsk!31 (* (- 1.0) y1uscore2dollarsk!33)))
               (* (+ x2uscore2dollarsk!32 (* (- 1.0) y2uscore2dollarsk!34))
                  (+ x2uscore2dollarsk!32 (* (- 1.0) y2uscore2dollarsk!34))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ y1uscore2dollarsk!33 (* (- 1.0) z1uscore2dollarsk!29))
                  (+ y1uscore2dollarsk!33 (* (- 1.0) z1uscore2dollarsk!29)))
               (* (+ y2uscore2dollarsk!34 (* (- 1.0) z2uscore2dollarsk!30))
                  (+ y2uscore2dollarsk!34 (* (- 1.0) z2uscore2dollarsk!30))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ x1uscore2dollarsk!31 (* (- 1.0) z1uscore2dollarsk!29))
                  (+ x1uscore2dollarsk!31 (* (- 1.0) z1uscore2dollarsk!29)))
               (* (+ x2uscore2dollarsk!32 (* (- 1.0) z2uscore2dollarsk!30))
                  (+ x2uscore2dollarsk!32 (* (- 1.0) z2uscore2dollarsk!30))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ x1uscore2dollarsk!31 (* (- 1.0) u1uscore2dollarsk!27))
                  (+ x1uscore2dollarsk!31 (* (- 1.0) u1uscore2dollarsk!27)))
               (* (+ x2uscore2dollarsk!32 (* (- 1.0) u2uscore2dollarsk!28))
                  (+ x2uscore2dollarsk!32 (* (- 1.0) u2uscore2dollarsk!28))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ y1uscore2dollarsk!33 (* (- 1.0) u1uscore2dollarsk!27))
                  (+ y1uscore2dollarsk!33 (* (- 1.0) u1uscore2dollarsk!27)))
               (* (+ y2uscore2dollarsk!34 (* (- 1.0) u2uscore2dollarsk!28))
                  (+ y2uscore2dollarsk!34 (* (- 1.0) u2uscore2dollarsk!28))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ z1uscore2dollarsk!29 (* (- 1.0) u1uscore2dollarsk!27))
                  (+ z1uscore2dollarsk!29 (* (- 1.0) u1uscore2dollarsk!27)))
               (* (+ z2uscore2dollarsk!30 (* (- 1.0) u2uscore2dollarsk!28))
                  (+ z2uscore2dollarsk!30 (* (- 1.0) u2uscore2dollarsk!28))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ x1 (* (- 1.0) y1)) (+ x1 (* (- 1.0) y1)))
               (* (+ x2 (* (- 1.0) y2)) (+ x2 (* (- 1.0) y2))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ y1 (* (- 1.0) z1)) (+ y1 (* (- 1.0) z1)))
               (* (+ y2 (* (- 1.0) z2)) (+ y2 (* (- 1.0) z2))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ x1 (* (- 1.0) z1)) (+ x1 (* (- 1.0) z1)))
               (* (+ x2 (* (- 1.0) z2)) (+ x2 (* (- 1.0) z2))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ x1 (* (- 1.0) u1)) (+ x1 (* (- 1.0) u1)))
               (* (+ x2 (* (- 1.0) u2)) (+ x2 (* (- 1.0) u2))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ y1 (* (- 1.0) u1)) (+ y1 (* (- 1.0) u1)))
               (* (+ y2 (* (- 1.0) u2)) (+ y2 (* (- 1.0) u2))))
            (* protectedzone protectedzone)))
(assert (>= (+ (* (+ z1 (* (- 1.0) u1)) (+ z1 (* (- 1.0) u1)))
               (* (+ z2 (* (- 1.0) u2)) (+ z2 (* (- 1.0) u2))))
            (* protectedzone protectedzone)))
(assert (not (>= (+ (* (+ x1uscore4dollarsk!9 (* (- 1.0) z1uscore4dollarsk!1))
                       (+ (* 2.0 d1uscore4dollarsk!10)
                          (* (- 2.0) f1uscore4dollarsk!2)))
                    (* (+ x2uscore4dollarsk!8 (* (- 1.0) z2uscore4dollarsk!0))
                       (+ (* 2.0 d2uscore4dollarsk!11)
                          (* (- 2.0) f2uscore4dollarsk!3))))
                 0.0)))
(check-sat)