(set-logic QF_NRA)

(declare-fun skoS3 () Real)
(declare-fun skoSX () Real)
(declare-fun skoX () Real)
(assert (and (= (* skoS3 skoS3) 3.) (and (not (<= skoX 0.)) (and (not (<= skoSX 0.)) (not (<= skoS3 0.))))))
(set-info :status sat)
(check-sat)