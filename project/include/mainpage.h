/*******************************************************************************
* Name            : mainpage
* Project         : mainpage
* Module          : ast
* Description     : doxygen comments
* Copyright       : 2017 Original Authors. All rights reserved.
* Original Authors : Dalton Stokke, Xukun Qin
* Modifications by : none
******************************************************************************/

#ifndef PROJECT_INCLUDE_MAINPAGE_H_
#define PROJECT_INCLUDE_MAINPAGE_H_


/*!  \mainpage DSL Project Index Page
\section into_sec Introduction
The purpose of this assignment is to convert a matlab type language
dubbed fcal, into c++ style format, with proper checking for syntatical,
semantical, and lexical errors.

\section members_sec Members
Xukun Qin 5188260
Dalton Stokke 4117123

\section test_sec Test

To test this program type :
make run-tests
You can also type :
make cpp
cpp is a target in the Makefile that will run the linter.

\section structure_sec Structure
This program utilizes multiple classes to function as nodes containing
information about various parts of our matlab type language.  Specifically
the token class in the scanner namespace and all classes that are members
of the ast namespace, these include the abstract super classes Node,
Program, Stmts, Stmt, Expr, and Decl, as well as all of their subsequent
sub-classes.  The classes in the ast namespace serve as members of an
Abstract Syntax Tree, the ast can be created by calling parse on a .dsl file
and this can also be undone by calling unparse to recreate that file.
See UML_Iteration3.pdf in project/ directory for more details on ast structure.

\section brief_sec Brief
This Brief is an arch-comment for each concrete class that inherits from the
abstract classes Program, Stmts, Stmt, Decl, and Expr: These classes will implement
their own defination of the unparse() funciton, and have their own constructors
which will take in different numbers of parameters, namely some assortment of
type std::string, Expr*, Decl*, Stmts*, and Stmt*. Some classes are further explanined
with more comments decribing unusual parameters or function.  See below.
*/

#endif  // PROJECT_INCLUDE_MAINPAGE_H_
