(set-logic QF_NRA)

(declare-fun skoY () Real)
(declare-fun skoX () Real)
(declare-fun pi () Real)
(assert (and (<= (* skoY (* skoY (+ (* skoX (* skoX (+ 1800000000000000000000000. (* skoX (* skoX 1800000000.))))) (* skoY (* skoY (+ (* skoX (* skoX (+ (- 150000000000000000000000.) (* skoX (* skoX (- 150000000.)))))) (* skoY (* skoY (+ (* skoX (* skoX (+ 5000000000000000000000. (* skoX (* skoX 5000000.))))) (* skoY (* skoY (+ (* skoX (* skoX (+ (/ (- 625000000000000000000.) 7.) (* skoX (* skoX (/ (- 625000.) 7.)))))) (* skoY (* skoY (* skoX (* skoX (+ (/ 62500000000000000000. 63.) (* skoX (* skoX (/ 62500. 63.)))))))))))))))))))) (* skoX (* skoX (+ 3600000000000000000000000. (* skoX (* skoX 3600000000.)))))) (and (not (<= pi (/ 15707963. 5000000.))) (and (not (<= (/ 31415927. 10000000.) pi)) (and (<= skoY (* pi (/ 1. 3.))) (and (<= (* pi (/ 1. 4.)) skoY) (and (<= skoX 120.) (<= 100. skoX))))))))
(set-info :status sat)
(check-sat)