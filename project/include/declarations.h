/*******************************************************************************
* Name            : declarations.h
* Project         : fcal
* Module          : ast
* Description     : forward declarations for Decl, Expr, Stmts, Stmt, Program
* Copyright       : 2017 Original Authors. All rights reserved.
* Original Authors : Dalton Stokke, Xukun Qin
* Modifications by : none
******************************************************************************/

#ifndef PROJECT_INCLUDE_DECLARATIONS_H_
#define PROJECT_INCLUDE_DECLARATIONS_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include <string>
#include "include/ast.h"
/*******************************************************************************
* Namespaces
******************************************************************************/
namespace fcal {
namespace ast {

/*******************************************************************************
* Forward Declarations
******************************************************************************/
/*! Decl is the base abstract class for declarations 
    in our fcal dsl language. 
*/
class Decl : public Node {
 public:
        virtual std::string unparse(void) {return " pure virtual ";}
        virtual std::string CppCode(void) {return " pure virtual ";}
}; /* Decl class */

/*! Program is the base abstract class for the start 
    of a program in our fcal dsl language.  
*/
class Program : public Node {
 public:
        virtual std::string unparse(void) {return " pure virtual ";}
        virtual std::string CppCode(void) {return " pure virtual ";}
}; /* Program class */

/*! Expr is the base abstract class for 
    expressions in our fcal dsl language.  
*/
class Expr : public Node {
 public:
        virtual std::string unparse(void) {return " pure virtual ";}
        virtual std::string CppCode(void) {return " pure virtual ";}
}; /* Expr class */

/*! Stmts is the base abstract class for
    statements in our fcal dsl language.
*/
class Stmts : public Node {
 public:
        virtual std::string unparse(void) {return " pure virtual ";}
        virtual std::string CppCode(void) {return " pure virtual ";}
}; /* Stmts class */

/*! Stmt is the base abstract class for a 
    statement in our fcal dsl language.
*/
class Stmt : public Node {
 public:
        virtual std::string unparse(void) {return " pure virtual ";}
        virtual std::string CppCode(void) {return " pure virtual ";}
}; /* Stmt class */

} /* namespace ast */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_DECLARATIONS_H_
