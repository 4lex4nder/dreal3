(set-logic QF_NRA)

(declare-fun skoX () Real)
(declare-fun pi () Real)
(declare-fun skoY () Real)
(assert (and (<= (* skoX (* skoX (+ (- 1.) (* skoX (* skoX (+ (/ 7. 24.) (* skoX (* skoX (+ (/ (- 1.) 45.) (* skoX (* skoX (+ (/ 29. 40320.) (* skoX (* skoX (+ (/ (- 23.) 1814400.) (* skoX (* skoX (/ 1. 7257600.)))))))))))))))))) 0.) (and (not (<= (* skoX (* skoX (/ (- 1.) 2.))) (- 1.))) (and (<= skoY (+ (/ (- 1.) 5.) (* pi (/ 1. 2.)))) (and (not (<= pi (/ 15707963. 5000000.))) (and (not (<= (/ 31415927. 10000000.) pi)) (and (<= (/ 1. 10.) skoX) (not (<= skoY skoX)))))))))
(set-info :status sat)
(check-sat)