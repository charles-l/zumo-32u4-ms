(define (init-motors)
    (call-c-func "init"))

;; ZUMO MOTORS ;;

(define (set-left-speed v rev)
    (call-c-func "set_left_speed" v rev))

(define (set-right-speed v rev)
    (call-c-func "set_right_speed" v rev))

(init-motors)
