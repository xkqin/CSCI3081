/*******************************************************************************
* Name            : stmt.h
* Project         : fcal
* Module          : ast
* Description     : Nonterminal Stmt subclasses
* Copyright       : 2017 Original Authors. All rights reserved.
* Original Authors : Dalton Stokke, Xukun Qin
* Modifications by : none
******************************************************************************/

#ifndef PROJECT_INCLUDE_STMT_H_
#define PROJECT_INCLUDE_STMT_H_

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

class declStmt : public Stmt {
 public:
        declStmt();
        explicit declStmt(Decl* d1) {_d = d1;}
        std::string unparse(void) {return _d -> unparse();}
        std::string CppCode(void) {return _d -> CppCode();}
 private:
        Decl* _d;
}; /* declStmt class */

class stmtsStmt : public Stmt {
 public:
        stmtsStmt();
        explicit stmtsStmt(Stmts* s1) {_s = s1;}
        std::string unparse(void) {return " { " + _s -> unparse() + " } ";}
        std::string CppCode(void) {return   _s -> CppCode() ;}
 private:
        Stmts* _s;
}; /* stmtStmt class */

class ifStmt : public Stmt {
 public:
        ifStmt();
        ifStmt(Stmt* s1, Expr* e1) {_s = s1; _e = e1;}
        std::string unparse(void) {return " if ( " + _e->unparse() + " ) "
                                                     + _s->unparse();}
        std::string CppCode(void) {return " if " + _e->CppCode() + "  \n"
      +std::string("{ \n    ") + _s->CppCode()+"\n"+std::string("}"); }
 private:
        Stmt* _s;
        Expr* _e;
}; /* ifStmt class */

class ifelseStmt : public Stmt {
 public:
        ifelseStmt();
        ifelseStmt(Stmt* s1, Stmt* s2, Expr* e1) {_s1 = s1;
        _s2 = s2; _e = e1;}
        std::string unparse(void) {return " if ( " + _e -> unparse() + " ) "
                        + _s1 -> unparse() + " else " + _s2 -> unparse();}
        std::string CppCode(void) {return "(" + _e->CppCode() + ")" +
        std::string(" ? ")+ _s1->CppCode()+" : "+_s2->CppCode();}
 private:
        Stmt* _s1;
        Stmt* _s2;
        Expr* _e;
}; /* ifelseStmt class */

class variableStmt : public Stmt {
 public:
        variableStmt();
        variableStmt(std::string s1, Expr* e1) {
          _lexeme = s1; _e1 = e1; boolean = 1;}
        variableStmt(std::string s1, Expr* e1, Expr* e2, Expr* e3) {
          _lexeme = s1; _e1 = e1; _e2 = e2; _e3 = e3; boolean = 0;}
        std::string unparse(void) {return (boolean) ? _lexeme + " = " +
                            _e1->unparse() + " ;\n" : _lexeme + " [ " +
                            _e1->unparse() + " : " + _e2->unparse() + " ] " +
                            " = " + _e3->unparse() + " ;\n";}
        std::string CppCode(void) {return (boolean) ? "    " + _lexeme + " = " +
        _e1->CppCode() + " ;\n" : "*("+ _lexeme +".access(" + _e1->CppCode()+","
        +_e2->CppCode()+"))"+" = "+ _e3->CppCode()+";\n";}
 private:
        int boolean;
        std::string _lexeme;
        Expr* _e1;
        Expr* _e2;
        Expr* _e3;
}; /* variableStmt class */

class printStmt : public Stmt {
 public:
    printStmt();
    explicit printStmt(Expr* e1) {_e = e1;}
    std::string unparse(void) {return " print ( " +
                                          _e->unparse() + " ) " + " ;\n";}
    std::string CppCode(void) {return "    cout << " + _e->CppCode() + ";\n";}
 private:
        Expr* _e;
}; /* printStmt class */

class repeatStmt : public Stmt {
 public:
        repeatStmt();
        repeatStmt(std::string lex, Expr* e1, Expr* e2, Stmt* s1) {
          _lexeme = lex; _e1 = e1; _e2 = e2; _s = s1;}
        std::string unparse(void) {return " repeat ( " + _lexeme + " = " +
                              _e1->unparse() + " to " + _e2->unparse() +
                              " ) " + _s->unparse();}
        std::string CppCode(void) {return "    for (" +
        _lexeme + " = " +_e1->CppCode()
        + "; "+ _lexeme+" <= "+_e2->CppCode()+
        "; "+_lexeme+" ++ ) {\n    "+_s->CppCode()+"\n"+std::string("   }");}

 private:
        Stmt* _s;
        std::string _lexeme;
        Expr* _e1;
        Expr* _e2;
}; /* repeatStmt class */

class whileStmt : public Stmt {
 public:
        whileStmt();
        whileStmt(Stmt* s1, Expr* e1) {_s = s1; _e = e1;}
        std::string unparse(void) {return " while ( " + _e->unparse() + " ) "
                              + _s->unparse();}
        std::string CppCode(void) {return " while ( " + _e->CppCode() + " ){\n"
                            + _s->CppCode()+"\n"+std::string("}\n");}
 private:
        Stmt* _s;
        Expr* _e;
}; /* whileStmt class */

class semiStmt : public Stmt {
 public:
        semiStmt() {}
        std::string unparse(void) {return " ;\n";}
        std::string CppCode(void) {return " ;\n    ";}
}; /* semiStmt class */

} /* namespace ast */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_STMT_H_
