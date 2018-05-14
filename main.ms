; vi: ft=scheme
(include "zumo-lib.ms")

(define (loop)
  (set-left-speed 400 #t)
  (set-right-speed 400 #t))

(forever loop)
