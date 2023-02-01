#lang plai-typed

;Define the misspelled animal class
(define-type MisspelledAnimal
  [caml (humps : number)]
  [yacc (height : number)])

;Construct two misspelled animals
(caml 2)
(yacc 1.9)

;Define a function which marks an animal as
;good if it can pass certain requirements
(define (good? [ma : MisspelledAnimal]) : boolean
(type-case MisspelledAnimal ma
[caml (humps) (>= humps 2)]
[yacc (height) (> height 2.1)]))

;Create two animal variables
(define ma1 (caml 2))
(define ma2 (yacc 1.9))

;Test if they are good
(test (good? ma1) #t)
(test (good? ma2) #f)

(define-type ArithC
[numC (n : number)]
[plusC (l : ArithC) (r : ArithC)]
[multC (l : ArithC) (r : ArithC)])

(define (parse [s : s-expression]) : ArithC
(cond
[(s-exp-number? s) (numC (s-exp->number s))]
[(s-exp-list? s)
(let ([sl (s-exp->list s)])
(case (s-exp->symbol (first sl))
[(+) (plusC (parse (second sl)) (parse (third sl)))]
[(*) (multC (parse (second sl)) (parse (third sl)))]
[else (error 'parse "invalid list input")]))]
[else (error 'parse "invalid input")]))

(define (nice? [mat : Ar]) : boolean
(type-case MisspelledAnimal ma
[caml (humps) (>= humps 2)]
[yacc (height) (> height 2.1)]))