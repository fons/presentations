;
;
; cl-mongo is asdf installable. I'm using sbcl in this demo so I can use require
;
(require :cl-mongo)
;
(require :cl-mongo-test)
;
(use-package :cl-mongo)
;
; I have a mongodb instance running on the localhost connected to the default port. 
; This command establishes a connection and switches to the "test" database. 
; In general, I've tried to stay as closely as possible to the javascript syntax 
; in the documentation.
;
(db.use "test")

;; preparation
;
; This will insert 50 elements into "foo". This was part of the pre-talk prep phase.
;
(cl-mongo-test::insert-lots "foo" 50)
(cl-mongo-test::insert-lots-more "foo" 100)
;
; 
; connection/show 
; The 'show command can be used with many keywords like :errors , :status etc.
; 
(show :connections)

;look at collection....
;
; The :all keyword will return all entries. In general however db.find will return one entry, so it's
; default behaviour is like 'findOne'. The :limit keyword can be used to retrieve a larger subset, or
; all entries when set to 0. 
;
(ret (db.count "foo" :all))

(pp (iter (db.find "foo" :all))) 
;
; (kv <key> <value> ) is cl-mongo's equivalent of the { : } key-value constructor in java script.
; (kv can also be used to group key-value pairs.
;
(pp (iter (db.find "foo" (kv "index-field" 100) )))

(pp (iter (db.find "foo" (kv "name" "weird") )))

(pp (iter (db.find "foo" (kv "name" "weird") :limit 0)))

;
; Indexing can be managed using the ($index ) macro. This is built on top of lower level constructs which
; are more in line with the javascript interface. This macro groups these facilities together and provides
; a common interface.
;
(show :indexes)

($index "foo" :asc "index-field")

(pp (iter (db.find "foo" :all :selector "index-field")))

($index "foo" :rm :all)

;
; This is a demonstration of the use of advanced queries in cl-mongo. The macro's below expand into key-value 
; pairs, but are a lot more readable.
;

(pp (db.find "foo" ($exists "k" t) :limit 1))
(pp (db.find "foo" ($not ($exists "k" t)) :limit 1))

(ret (db.count "foo" ($not ($exists "k" t))))
(ret (db.count "foo" ($not ($exists "k" nil))))

(pp (db.find "foo" ($> "k" 56) :limit 1))

(pp (db.find "foo" ($> "k" 56) :selector "k" :limit 1))

(pp (db.find "foo" ($not ($mod "k" (10 1))) :limit 0 ))

;
; You can define functions in common lisp (1) which are translated into javascript and stored on the client
; or the server. For all intents and purposes these functions behave like regular lisp functions, except that
; they get executed on the mongodb server.
; 
; (1) I use parenscript for this. Although it does an excellent job, it requires a few idiomatic changes 
;     to your lisp code. The most obvious one is that you need to explicitly specify 
;     an exit point using return. See the parenscript reference guide for details.

;
; This is a regular lisp function, echoing back the input on the repl.
;
(defun echo* (x) x)

;
; The defjs macro translates lisp to javascript and stores it on the client side. (echo 1) now runs on
; the server's javascript engine.

(defjs echo (x) (return x)) 

;
; Similarly, defsrvjs macro stores the generated javascript on the server side, in the ..systems collection.
; 
(defsrvjs echo_s (x) (return x)) 

(defsrvjs plus(x) (return (+ 10 x)))

;
; map-reduce : count the number of documents with a distinct name
;
; cl-mongo-test::insert-lots and cl-mongo::insert-lots-more inserted elements with different
; values for the "name" key.
;

(ret (db.distinct "foo" "name" ))

;
; This mapping function will assign each distinct name the value 9.
;
(defjs map_keys()
   (emit this.name 9))

;
; The reduction will add up the values the map function assigned to each key. 
; There are two groups of 50 entries and 100 entries respectively, so we expect 50* 9 and 100 * 9 
; as distinct values at the end of the resuction.
;
(defjs sumreduce(k vals)
  (let ((sum 0))
    (dolist (c vals)
      (incf sum c))
    (return sum)))
		    
;
; Notice that I use client side javascript. I pass in the name of the function (no quotes) to the 
; $map-reduce macro.
;
(pp (mr.p ($map-reduce "foo" map_keys sumreduce)))

						     
