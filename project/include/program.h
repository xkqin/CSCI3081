/*******************************************************************************
* Name            : program.h
* Project         : fcal
* Module          : scanner
* Description     : Header file for program.cc
* Copyright       : 2017 Original Authors. All rights reserved.
* Original Authors : Dalton Stokke, Xukun Qin
* Modifications by : none
******************************************************************************/

#ifndef PROJECT_INCLUDE_PROGRAM_H_
#define PROJECT_INCLUDE_PROGRAM_H_

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

class program : public Program {
 public:
        program();
        program(std::string lex, Stmts* s) { _lexeme = lex;  _s = s;}
        std::string unparse() {
          return _lexeme + " () {\n" + _s->unparse() + "}";}
        std::string CppCode() {
          return
          "#include <iostream>\n"+
          std::string("#include \"include/Matrix.h\"\n#include <math.h>\n") +
          std::string("using namespace std;\nint ") +
           _lexeme + std::string(" ( ) {\n")+
            _s->CppCode() + std::string("\n}");
        }
 private:
        std::string _lexeme;
        Stmts* _s;
}; /* program class */

} /* namespace ast */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_PROGRAM_H_
