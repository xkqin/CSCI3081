/*******************************************************************************
* Name            : decl.h
* Project         : fcal
* Module          : ast
* Description     : Nonterminal Decl subclasses
* Copyright       : 2017 Original Authors. All rights reserved.
* Original Authors : Dalton Stokke, Xukun Qin
* Modifications by : none
******************************************************************************/

#ifndef PROJECT_INCLUDE_DECL_H_
#define PROJECT_INCLUDE_DECL_H_

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

/*! matrixDecl handles production 17)
Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr ';'
  */
class matrixDecl : public Decl {
 public:
        matrixDecl();
	/*! This constructor requires six parameters: 3 string 3 pointers of Expr
            \param var1 a string which require for a matrix Decl
            \param e1 a Expr pointer
            \param e2 a Expr pointer
            \param var2 a string
            \param var3 a string
            \param e3 a Expr pointer
	 */
        matrixDecl(std::string var1, Expr* e1, Expr* e2,
                                std::string var2, std::string var3, Expr* e3) {
          _lexeme1 = var1;
          _lexeme2 = var2;
          _lexeme3 = var3;
          _e1 = e1;
          _e2 = e2;
          _e3 = e3;
        }
        std::string unparse(void) {return " matrix " + _lexeme1 + " [ " +
             _e1->unparse() + " : " + _e2->unparse() + " ] " + _lexeme2 + " : "
             + _lexeme3 + " = " + _e3->unparse() + " ;\n";}
        std::string CppCode(void) {return "matrix " +_lexeme1
        + "( "+_e1->CppCode()+","+_e2->CppCode()+" ) ;\n"
             +std::string("    for (int ")+_lexeme2+" = 0"+
            "; "+_lexeme2 + " < "+_e1->CppCode()+"; "+_lexeme2+" ++ ) {\n"+
            std::string("        for (int ")+_lexeme3+" = 0"+
           "; "+_lexeme3 + " < "+_e2->CppCode()+"; "+_lexeme3+" ++ ) {\n"+
            "    *("+_lexeme1+".access("+_lexeme2+","+
            _lexeme3+")) = "+_e3->CppCode()+";\n"+
            std::string("}\n")+std::string("}\n");}

 private:
        std::string _lexeme1;
        std::string _lexeme2;
        std::string _lexeme3;
        Expr* _e1;
        Expr* _e2;
        Expr* _e3;
}; /* matrixDecl2 class */

/*! matrixDecl2 handles production 18)
Decl ::= 'matrix' varName '=' Expr ';'
*/

class matrixDecl2 : public Decl {
 public:
        matrixDecl2();
	/*! This constructor requires two parameters: a string and a Expr pointer
            \param s1 is a string
            \param e2 a pointer pointing to a Expr
	*/
        matrixDecl2(std::string s1, Expr* e2) {
          _s1 = s1;
          _e1 = e2;
        }
        std::string unparse(void) {return " matrix " + _s1 + " = "
           + _e1->unparse() + " ;\n"; }
        std::string CppCode(void) {return "    matrix " + _s1 + " ( "+
           _e1->CppCode() + " ); \n";}
 private:
        std::string _s1;
        Expr* _e1;
}; /* matrixDecl2 class */

class intDecl : public Decl {
 public:
        intDecl();
	/*! This constructor requires one parameters: string that is the var name
            \param s1 the string which is the var name
	*/
        explicit intDecl(std::string s1) {_lexeme = s1;}
        std::string unparse(void) {return " int " + _lexeme + " ;\n";}
        std::string CppCode(void) {return "    int " + _lexeme + " ;\n";}
 private:
        std::string _lexeme;  // varName
}; /* intDecl class */

class floatDecl : public Decl {
 public:
        floatDecl();
        /*! This constructor requires one parameters: string that is the var name
            \param s1 the string which is the var name
	*/
        explicit floatDecl(std::string s1) {_lexeme = s1;}
        std::string unparse(void) {return " float " + _lexeme + " ;\n";}
        std::string CppCode(void) {return "    float " + _lexeme + " ;\n";}
 private:
        std::string _lexeme;  // varName
}; /* floatDecl class */

class stringDecl : public Decl {
 public:
        stringDecl();
        /*! This constructor requires one parameters: string that is the var name
            \param s1 the string which is the var name
	*/
        explicit stringDecl(std::string s1) {_lexeme = s1;}
        std::string unparse(void) {return " string " + _lexeme + " ;\n";}
        std::string CppCode(void) {return "    string " + _lexeme + " ;\n";}
 private:
        std::string _lexeme;  // varName
}; /* stringDecl class */

class booleanDecl : public Decl {
 public:
        booleanDecl();
        explicit booleanDecl(std::string s1) {_lexeme = s1;}
        std::string unparse(void) {return " boolean " + _lexeme + " ;\n";}
        std::string CppCode(void) {return "    boolean " + _lexeme + " ;\n";}
 private:
        std::string _lexeme;  // varName
};  /* booleanDecl class */



}  /* namespace ast */
}  /* namespace fcal */

#endif  // PROJECT_INCLUDE_DECL_H_
