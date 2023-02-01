;Define language
#lang slideshow

;Define a circle and rectangle
(define c (circle 50))
(define r (rectangle 25 50))

;Print circle, rectangle, circle, appended as one object
(hc-append c r c)

;Define a square
(define (square n)
  (filled-rectangle n n))

;Print a square of size 50
(square 50)

;"Function" which defines a checker pattern
(define (checker p1 p2)
  (let ([p12 (hc-append p1 p2)]
        [p21 (hc-append p2 p1)])
    (vc-append p12 p21)))

;Give colors to the checker squares
(checker (colorize (square 10) "red")
           (colorize (square 10) "black"))

;Define a series of objects combined into one
(define (series mk)
  (hc-append 4 (mk 5) (mk 10) (mk 20)))

;Prints 4 of an object in a square
(define (four p)
  (define two-p (hc-append p p))
  (vc-append two-p two-p))

;Combines different functions to create larger checker board
(define (checkerboard p)
  (let* ([rp (colorize p "red")]
         [bp (colorize p "black")]
         [c (checker rp bp)]
         [c4 (four c)])
    (four c4)))

;Creates a series of circles
(series circle)

;Using lambda to create an anonymous function
(series (lambda (size) (checkerboard (square size))))

;In the following rgb-series function, the uses of mk in each
;lambda form refer to the argument of rgb-series,
;since that’s the binding that is textually in scope:
(define (rgb-series mk)
  (vc-append
   (series (lambda (sz) (colorize (mk sz) "red")))
   (series (lambda (sz) (colorize (mk sz) "green")))
   (series (lambda (sz) (colorize (mk sz) "blue")))))

(rgb-series square)

;Here’s another example, where rgb-maker takes a function
;and returns a new one that remembers and uses the
;original function.
(define (rgb-maker mk)
  (lambda (sz)
    (vc-append (colorize (mk sz) "red")
               (colorize (mk sz) "green")
               (colorize (mk sz) "blue"))))

;The list function takes any number of arguments and returns
;a list containing the given values:
(list "red" "green" "blue")