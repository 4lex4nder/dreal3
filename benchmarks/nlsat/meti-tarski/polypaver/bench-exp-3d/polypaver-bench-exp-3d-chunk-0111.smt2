(set-logic QF_NRA)

(declare-fun skoZ () Real)
(declare-fun skoY () Real)
(declare-fun skoX () Real)
(assert (and (not (<= (* skoZ (+ (+ (+ 60. (* skoX (+ (- 36.) (* skoX (+ 9. (* skoX (- 1.))))))) (* skoY (+ (+ (- 36.) (* skoX (+ 18. (* skoX (- 3.))))) (* skoY (+ (+ 9. (* skoX (- 3.))) (* skoY (- 1.))))))) (* skoZ (+ (+ (+ (- 48.) (* skoX (+ 21. (* skoX (- 3.))))) (* skoY (+ (+ 21. (* skoX (- 6.))) (* skoY (- 3.))))) (* skoZ (+ (+ (+ 11. (* skoX (- 3.))) (* skoY (- 3.))) (* skoZ (- 1.)))))))) (+ (+ (- 120.) (* skoX (+ 60. (* skoX (+ (- 12.) skoX))))) (* skoY (+ (+ 60. (* skoX (+ (- 24.) (* skoX 3.)))) (* skoY (+ (+ (- 12.) (* skoX 3.)) skoY))))))) (and (<= 0. skoX) (and (<= 0. skoY) (and (<= 0. skoZ) (and (<= skoX 1.) (and (<= skoY 1.) (and (<= skoZ 1.) (and (<= skoZ (+ (+ 2. (* skoX (- 1.))) (* skoY (- 1.)))) (<= (+ (+ 2. (* skoX (- 1.))) (* skoY (- 1.))) skoZ))))))))))
(set-info :status sat)
(check-sat)