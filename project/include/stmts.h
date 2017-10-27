/*******************************************************************************
* Name            : stmts.h
* Project         : fcal
* Module          : ast
* Description     : Nonterminal Stmts subclasses
* Copyright       : 2017 Original Authors. All rights reserved.
* Original Authors : Dalton Stokke, Xukun Qin
* Modifications by : none
******************************************************************************/

#ifndef PROJECT_INCLUDE_STMTS_H_
#define PROJECT_INCLUDE_STMTS_H_

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

class emptyStmts : public Stmts {
 public:
      std::string unparse(void) {return "";}
      std::string CppCode(void){return "";}
};
/*! This class seqStmts is the subclass of the abstract class Stmts
 */
class seqStmts : public Stmts {
 public:
      seqStmts();
      /*! This constructor requires two parameters: pointer Stmt and pointer Stmts
          \param s1 the pointer poiting to a Stmt class
          \param s2 the pointer poiting to a Stmts class

       */
      seqStmts(Stmt* s1, Stmts* s2) {_s = s1; _sS = s2;}
      std::string unparse(void) {return _s -> unparse() + _sS -> unparse();}
      std::string CppCode(void) {return _s -> CppCode() + _sS -> CppCode();}
 private:
      Stmt* _s;
      Stmts* _sS;
};


} /* namespace ast */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_STMTS_H_
