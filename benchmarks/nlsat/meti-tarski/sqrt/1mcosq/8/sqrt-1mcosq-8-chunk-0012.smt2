(set-logic QF_NRA)

(declare-fun pi () Real)
(declare-fun skoX () Real)
(declare-fun skoY () Real)
(assert (and (not (<= skoY (+ (/ (- 1.) 5.) (* pi (/ 1. 2.))))) (and (not (<= pi (/ 15707963. 5000000.))) (and (not (<= (/ 31415927. 10000000.) pi)) (and (<= (/ 1. 10.) skoX) (not (<= skoY skoX)))))))
(set-info :status sat)
(check-sat)