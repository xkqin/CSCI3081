/*******************************************************************************
* Name            : expr.h
* Project         : fcal
* Module          : ast
* Description     : Nonterminal Expr subclasses
* Copyright       : 2017 Original Authors. All rights reserved.
* Original Authors : Dalton Stokke, Xukun Qin
* Modifications by : none
******************************************************************************/

#ifndef PROJECT_INCLUDE_EXPR_H_
#define PROJECT_INCLUDE_EXPR_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include <string>

#include "include/declarations.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace fcal {
namespace ast {

/*******************************************************************************
* Forward Declarations
******************************************************************************/

class plusExpr : public Expr {
 public:
        plusExpr();
        plusExpr(Expr* e1, Expr* e2) {_e1 = e1; _e2 = e2;}
        std::string unparse(void) {return _e1->unparse() + " + "
                                                 + _e2 -> unparse();}
        std::string CppCode(void) {return "(" + _e1->CppCode() + " + "
                                        + _e2 -> CppCode() + ")" ;}
 private:
        Expr* _e1;
        Expr* _e2;
}; /* plusExpr class */

class minusExpr : public Expr {
 public:
        minusExpr();
        minusExpr(Expr* e1, Expr* e2) {_e1 = e1; _e2 = e2;}
        std::string unparse(void) {return _e1 -> unparse() + " - "
                                                 + _e2 -> unparse();}
        std::string CppCode(void) {return "(" + _e1->CppCode() +" - "
                                        + _e2 -> CppCode() + ")" ;}

 private:
        Expr* _e1;
        Expr* _e2;
}; /* minusExpr class */

class divExpr : public Expr {
 public:
        divExpr();
        divExpr(Expr* e1, Expr* e2) {_e1 = e1; _e2 = e2;}
        std::string unparse(void) {return _e1 -> unparse() + " / "
                                                 + _e2 -> unparse();}
        std::string CppCode(void) {return "(" + _e1->CppCode() +" / "
                                        + _e2 -> CppCode() + ")" ;}
 private:
        Expr* _e1;
        Expr* _e2;
}; /* divExpr class */

class mulExpr : public Expr {
 public:
        mulExpr();
        mulExpr(Expr* e1, Expr* e2) {_e1 = e1; _e2 = e2;}
        std::string unparse(void) {return _e1 -> unparse() + " * "
                                                 + _e2 -> unparse();}
        std::string CppCode(void) {return "(" + _e1->CppCode() +" * "
                                        + _e2 -> CppCode() + ")" ;}
 private:
        Expr* _e1;
        Expr* _e2;
}; /* mulExpr class */

/*! relationshipExpr class handles the following productions:
// Expr ::= Expr equalEquals Expr ==
// Expr ::= Expr lessThanEquals Expr <=
// Expr ::= Expr greaterThanEquals Expr >=
// Expr ::= Expr notEquals Expr !=
// Expr ::= Expr leftAngle Expr <
// Expr ::= Expr rightAngle Expr >
*/
class relationshipExpr : public Expr {
 public:
        relationshipExpr();
        relationshipExpr(Expr* e1, std::string s, Expr* e2) {_e1 = e1;
          _s1 = s;  _e2 = e2;}
        std::string unparse(void) {return _e1 -> unparse() + " " + _s1 + " "
                                                + _e2 -> unparse();}
        std::string CppCode(void) {return "(" + _e1 -> CppCode() +
                            " " + _s1 + " "+ _e2 -> CppCode() + ")";}
 private:
       Expr* _e1;
       Expr* _e2;
       std::string _s1;
}; /* relationshipExpr class */

class andExpr : public Expr {
 public:
        andExpr();
        andExpr(Expr* e1, Expr* e2) {_e1 = e1; _e2 = e2;}
        std::string unparse(void) {return _e1 -> unparse() + " && "
                                                 + _e2 -> unparse();}
        std::string CppCode(void) {return "("+ _e1 -> unparse() +
                                    " && "+ _e2 -> unparse() + ")";}
 private:
        Expr* _e1;
        Expr* _e2;
}; /* andExpr class */

class orExpr : public Expr {
 public:
        orExpr();
        orExpr(Expr* e1, Expr* e2) {_e1 = e1; _e2 = e2;}
        std::string unparse(void) {return _e1 -> unparse() + " || "
                                                 + _e2 -> unparse();}
        std::string CppCode(void) {return "("+ _e1 -> unparse() +
                                    " || "+ _e2 -> unparse() + ")";}
 private:
        Expr* _e1;
        Expr* _e2;
}; /* orExpr class */

class varExpr : public Expr {
 public:
        varExpr();
        explicit varExpr(std::string s1) {_lexeme = s1;}
        std::string unparse(void) {return _lexeme;}
        std::string CppCode(void) {return _lexeme;}
 private:
        std::string _lexeme;
}; /* varExpr class */

class constExpr : public Expr {
 public:
        constExpr();
        explicit constExpr(std::string s1) {_lexeme = s1;}
        std::string unparse(void) {return _lexeme;}
        std::string CppCode(void) {return _lexeme;}
 private:
        std::string _lexeme;
}; /* constExpr class */

class booleanExpr : public Expr {
 public:
        booleanExpr();
        explicit booleanExpr(int i1) {boolean = i1;}
        std::string unparse(void) {return (boolean) ? " True " : " False ";}
        std::string CppCode(void) {return (boolean) ? " True " : " False ";}
 private:
        int boolean;
}; /* stringExpr class */

class MatrixExpr : public Expr {
 public:
        MatrixExpr();
        MatrixExpr(std::string s1, Expr* e1, Expr* e2) {_lexeme = s1;
          _e1 = e1;
          _e2 = e2;
        }
        std::string unparse(void) {
          return _lexeme + " [ " + _e1 -> unparse() + " : "
                        + _e2 -> unparse() + " ] ";}
        std::string CppCode(void) {return "*("+ _lexeme +".access(" +
         _e1->CppCode()+","+_e2->CppCode()+"))";}
 private:
        std::string _lexeme;
        Expr* _e1;
        Expr* _e2;
}; /* MatrixExpr class */

class nestedExpr : public Expr {
 public:
        nestedExpr();
        nestedExpr(std::string s1, Expr* e1) {_lexeme = s1; _e1 = e1;}
        std::string unparse(void) {return _lexeme + " ( " +
                                          _e1 -> unparse() + " ) ";}
        std::string CppCode(void) {
            if (_lexeme == "n_rows" || _lexeme == "n_cols") {
                return _e1->CppCode() + "." + _lexeme + "()";
            } else if (_lexeme == "matrix_read") {
              return "matrix::" + _lexeme +" (" +_e1->CppCode()+") ";
            } else {
            return _lexeme + " ( " + _e1->CppCode() + " ) ";}
        }
 private:
        std::string _lexeme;
        Expr* _e1;
}; /* nestedExpr class */

class functionCallExpr : public Expr {
 public:
        functionCallExpr();
        explicit functionCallExpr(Expr* e1) {_e1 = e1;}
        std::string unparse(void) {return " ( " + _e1 -> unparse() + " ) ";}
        std::string CppCode(void) {return " ( " + _e1 -> CppCode() + " ) ";}
 private:
        Expr* _e1;
}; /* functionCallExpr class */

class letExpr : public Expr {
 public:
        letExpr();
        letExpr(Stmts* s1, Expr* e1) {_s1 = s1; _e1 = e1;}
        std::string unparse(void) {return " let " + _s1 -> unparse() + " in "
                                                + _e1 ->unparse() + " end ";}
        std::string CppCode(void) {return "({" + _s1->CppCode() + "(" +
                                                 _e1->CppCode() + ") ;\n})";}
 private:
        Stmts* _s1;
        Expr* _e1;
}; /* letExpr class */

class ifExpr : public Expr {
 public:
        ifExpr();
        ifExpr(Expr* e1, Expr* e2, Expr* e3) {
          _e1 = e1; _e2 = e2; _e3 = e3;}
        std::string unparse(void) {return " if " + _e1 -> unparse() + " then "
                              + _e2 -> unparse() + " else " + _e3 -> unparse();}
        std::string CppCode(void) {return  "(" + _e1->CppCode() + ") ? (" +
                     _e2->CppCode() + ") : " + _e3->CppCode(); }
 private:
        Expr* _e1;  // string
        Expr* _e2;
        Expr* _e3;
}; /* ifExpr class */

class notExpr : public Expr {
 public:
        notExpr();
        explicit notExpr(Expr* e1) {_e1 = e1;}
        std::string unparse(void) {return " ! " + _e1->unparse();}
        std::string CppCode(void) {return "!" + _e1->CppCode();}
 private:
        Expr* _e1;
}; /* notExpr class */

} /* namespace ast */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_EXPR_H_
