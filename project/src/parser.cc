/*******************************************************************************
 * Name            : parser.h
 * Project         : fcal
 * Module          : parser
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Erik Van Wyk
 * Modifications by: Dan Challou, John Harwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/parser.h"
#include <assert.h>
#include <stdio.h>
#include "include/ext_token.h"
#include "include/scanner.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace parser {


/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Parser::~Parser() {
  if (scanner_) delete scanner_;

  scanner::ExtToken *to_delete1;
  curr_token_ = tokens_;
  while (curr_token_) {
    to_delete1 = curr_token_;
    curr_token_ = curr_token_->next();
    delete to_delete1;
  } /* while() */

  scanner::Token *curr_scanner_token = stokens_;
  scanner::Token *to_delete2;
  while (curr_scanner_token) {
    to_delete2 = curr_scanner_token;
    curr_scanner_token = curr_scanner_token->next();
    delete to_delete2;
  } /* while() */
} /* Parser::~Parser() */

ParseResult Parser::Parse(const char *text) {
  assert(text != NULL);

  ParseResult pr;
  try {
  scanner_ = new scanner::Scanner();
  stokens_ = scanner_->Scan(text);
  tokens_ = tokens_->ExtendTokenList(this, stokens_);

  assert(tokens_ != NULL);
  curr_token_ = tokens_;
  pr = ParseProgram();
  }
  catch (std::string errMsg) {
     pr.ok(false);
     pr.errors(errMsg);
     pr.ast(NULL);
  }
  return pr;
} /* Parser::parse() */

/*
 * parse methods for non-terminal symbols
 * --------------------------------------
 */

// Program
ParseResult Parser::ParseProgram() {
  ParseResult pr;
  // root
  // Program ::= varName '(' ')' '{' Stmts '}'
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  match(scanner::kLeftParen);
  match(scanner::kRightParen);
  match(scanner::kLeftCurly);
  ParseResult pr_stmts = parse_stmts();
  match(scanner::kRightCurly);
  match(scanner::kEndOfFile);
  fcal::ast::program *p = new fcal::ast::program(name,
    reinterpret_cast<fcal::ast::Stmts*>(pr_stmts.ast()));
  pr.ast(p);
  return pr;
} /* Parser::ParseProgram() */

// MatrixDecl
// identical purpose of parse_decl, handles special matrix syntax.
ParseResult Parser::parse_matrix_decl() {
  ParseResult pr;
  match(scanner::kMatrixKwd);
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  // Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '='
  // Expr ';'
  if (attempt_match(scanner::kLeftSquare)) {
    ParseResult p1 = parse_expr(0);
    match(scanner::kColon);
    ParseResult p2 = parse_expr(0);
    match(scanner::kRightSquare);
    match(scanner::kVariableName);
    std::string name1(prev_token_->lexeme());
    // parse_variable_name();
    match(scanner::kColon);
    // parse_variable_name();
    match(scanner::kVariableName);
    std::string name2(prev_token_->lexeme());
    match(scanner::kAssign);
    fcal::ast::matrixDecl *md = new fcal::ast::matrixDecl(name,
      reinterpret_cast<fcal::ast::Expr*>(p1.ast()),
      reinterpret_cast<fcal::ast::Expr*>(p2.ast()),
    name1, name2, reinterpret_cast<fcal::ast::Expr*>(parse_expr(0).ast()));
    pr.ast(md);
  } else if (attempt_match(scanner::kAssign)) {
    // Decl ::= 'matrix' varName '=' Expr ';'
    fcal::ast::matrixDecl2 *md2 = new fcal::ast::matrixDecl2(name,
      reinterpret_cast<fcal::ast::Expr*>(parse_expr(0).ast()));
    pr.ast(md2);
  } else {
    throw((std::string) "Bad Syntax of Matrix Decl in in parseMatrixDecl");
  }

  match(scanner::kSemiColon);

  return pr;
}
// standardDecl
// Decl ::= integerKwd varName | floatKwd varName | stringKwd varName
ParseResult Parser::parse_standard_decl() {
  ParseResult pr;

  if (attempt_match(scanner::kIntKwd)) {
     // Type ::= intKwd
     match(scanner::kVariableName);
     fcal::ast::intDecl *it = new fcal::ast::intDecl(prev_token_->lexeme());
     pr.ast(it);
  } else if (attempt_match(scanner::kFloatKwd)) {
    // Type ::= floatKwd
    match(scanner::kVariableName);
    fcal::ast::floatDecl *fl = new fcal::ast::floatDecl(prev_token_->lexeme());
    pr.ast(fl);
  } else if (attempt_match(scanner::kStringKwd)) {
    // Type ::= stringKwd
    match(scanner::kVariableName);
    fcal::ast::stringDecl *sd =
     new fcal::ast::stringDecl(prev_token_->lexeme());
    pr.ast(sd);
  } else if (attempt_match(scanner::kBoolKwd)) {
    // Type ::= boolKwd
    match(scanner::kVariableName);
    fcal::ast::booleanDecl *bd =
     new fcal::ast::booleanDecl(prev_token_->lexeme());
    pr.ast(bd);
  }
  // match(scanner::kVariableName);
  match(scanner::kSemiColon);
  return pr;
}

// Decl
ParseResult Parser::parse_decl() {
  ParseResult pr;
  // Decl :: matrix variableName ....
  if (next_is(scanner::kMatrixKwd)) {
    pr = parse_matrix_decl();
  } else {
    // Decl ::= Type variableName semiColon
    pr = parse_standard_decl();
  }
  return pr;
}

// Stmts
ParseResult Parser::parse_stmts() {
  ParseResult pr;
  if (!next_is(scanner::kRightCurly) && !next_is(scanner::kInKwd)) {
    // Stmts ::= Stmt Stmts
    ParseResult pr_stmt = parse_stmt();
    ParseResult pr_stmts = parse_stmts();
    fcal::ast::seqStmts *sq =
     new fcal::ast::seqStmts(reinterpret_cast<fcal::ast::Stmt*>(pr_stmt.ast()),
     reinterpret_cast<fcal::ast::Stmts*> (pr_stmts.ast()));
    pr.ast(sq);
    // pr.ast(seqStmts(pr_stmt.ast(), pr_stmts.ast()));
  } else {
    fcal::ast::emptyStmts *es = new fcal::ast::emptyStmts();
    pr.ast(es);
    // Stmts ::=
    // nothing to match.k
  }
  return pr;
}

// Stmt
ParseResult Parser::parse_stmt() {
  ParseResult pr;

  // Stmt ::= Decl
  if (next_is(scanner::kIntKwd) || next_is(scanner::kFloatKwd) ||
      next_is(scanner::kMatrixKwd) || next_is(scanner::kStringKwd) ||
      next_is(scanner::kBoolKwd)) {
    fcal::ast::declStmt *ds = new fcal::ast::declStmt(
      reinterpret_cast<fcal::ast::Decl*> (parse_decl().ast()));
    pr.ast(ds);
  } else if (attempt_match(scanner::kLeftCurly)) {
    // Stmt ::= '{' Stmts '}'
    fcal::ast::stmtsStmt *ss = new fcal::ast::stmtsStmt(
      reinterpret_cast<fcal::ast::Stmts*>(parse_stmts().ast()));
    match(scanner::kRightCurly);
    pr.ast(ss);
  } else if (attempt_match(scanner::kIfKwd)) {
    // Stmt ::= 'if' '(' Expr ')' Stmt
    // Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    match(scanner::kLeftParen);
    ParseResult pe = parse_expr(0);
    match(scanner::kRightParen);
    ParseResult ps = parse_stmt();
    fcal::ast::ifStmt *i = new fcal::ast::ifStmt(
      reinterpret_cast<fcal::ast::Stmt*> (ps.ast()),
      reinterpret_cast<fcal::ast::Expr*>(pe.ast()));
    pr.ast(i);

    if (attempt_match(scanner::kElseKwd)) {
      fcal::ast::ifelseStmt *ie = new fcal::ast::ifelseStmt(
        reinterpret_cast<fcal::ast::Stmt*>(ps.ast()),
        reinterpret_cast<fcal::ast::Stmt*>(parse_stmt().ast()),
        reinterpret_cast<fcal::ast::Expr*>(pe.ast()));
      pr.ast(ie);
    }

  } else if (attempt_match(scanner::kVariableName)) {
    /*
     * Stmt ::= varName '=' Expr ';'  | varName '[' Expr ':' Expr ']'
     * '=' Expr ';'
     */
     std::string name(prev_token_ -> lexeme());
     ParseResult e1;
     ParseResult e2;
     bool ok = false;
    if (attempt_match(scanner::kLeftSquare)) {
      e1 = parse_expr(0);
      match(scanner::kColon);
      e2 = parse_expr(0);
      match(scanner::kRightSquare);
      ok = true;
    }
    match(scanner::kAssign);
    ParseResult e3 = parse_expr(0);
    match(scanner::kSemiColon);
    if (ok) {
      fcal::ast::variableStmt *v1 =  new fcal::ast::variableStmt(name,
       reinterpret_cast<fcal::ast::Expr*>(e1.ast()),
       reinterpret_cast<fcal::ast::Expr*>(e2.ast()),
       reinterpret_cast<fcal::ast::Expr*>(e3.ast()));
      pr.ast(v1);
    } else {
      fcal::ast::variableStmt *v2 = new fcal::ast::variableStmt(name,
        reinterpret_cast<fcal::ast::Expr*>(e3.ast()));
      pr.ast(v2);
    }
  } else if (attempt_match(scanner::kPrintKwd)) {
    // Stmt ::= 'print' '(' Expr ')' ';'
    match(scanner::kLeftParen);
    ParseResult p = parse_expr(0);
    match(scanner::kRightParen);
    match(scanner::kSemiColon);
    fcal::ast::printStmt *p1 = new fcal::ast::printStmt(
      reinterpret_cast<fcal::ast::Expr*>(p.ast()));
    pr.ast(p1);
  } else if (attempt_match(scanner::kRepeatKwd)) {
    // Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
    match(scanner::kLeftParen);
    match(scanner::kVariableName);
    std::string name(prev_token_ -> lexeme());
    match(scanner::kAssign);
    ParseResult e1 = parse_expr(0);
    match(scanner::kToKwd);
    ParseResult e2 = parse_expr(0);
    match(scanner::kRightParen);
    fcal::ast::repeatStmt *r =  new fcal::ast::repeatStmt (name,
     reinterpret_cast<fcal::ast::Expr*>(e1.ast()),
     reinterpret_cast<fcal::ast::Expr*>(e2.ast()),
     reinterpret_cast<fcal::ast::Stmt*>(parse_stmt().ast()));
    pr.ast(r);
  } else if (attempt_match(scanner::kWhileKwd)) {
    // Stmt ::= 'while' '(' Expr ')' Stmt
    match(scanner::kLeftParen);
    ParseResult e = parse_expr(0);
    match(scanner::kRightParen);
    ParseResult s = parse_stmt();
    fcal::ast::whileStmt *w = new fcal::ast::whileStmt(
      reinterpret_cast<fcal::ast::Stmt*>(s.ast()),
      reinterpret_cast<fcal::ast::Expr*>(e.ast()));
    pr.ast(w);
  } else if (attempt_match(scanner::kSemiColon)) {
    // Stmt ::= ';
    // parsed a skip
    fcal::ast::semiStmt *s = new fcal::ast::semiStmt();
    pr.ast(s);
  } else {
    // const char *printer = curr_token_->lexeme().std::string::c_str();
    // printf("\n%s", printer);
    // fflush(stdout);
    throw(make_error_msg(curr_token_->terminal()) +
          " while parsing a statement");
  }
  // Stmt ::= variableName assign Expr semiColon
  return pr;
}

// Expr
ParseResult Parser::parse_expr(int rbp) {
  /* Examine current token, without consuming it, to call its
     associated parse methods.  The ExtToken objects have 'nud' and
     'led' methods that are dispatchers that call the appropriate
     parse methods.*/
  ParseResult left = curr_token_->nud();

  while (rbp < curr_token_->lbp()) {
    left = curr_token_->led(left);
  }

  return left;
}

/*
 * parse methods for Expr productions
 * ----------------------------------
 */

// Expr ::= trueKwd
ParseResult Parser::parse_true_kwd() {
  ParseResult pr;
  match(scanner::kTrueKwd);
  fcal::ast::booleanExpr *be = new fcal::ast::booleanExpr(1);
  pr.ast(be);
  return pr;
}

// Expr ::= trueKwd
ParseResult Parser::parse_false_kwd() {
  ParseResult pr;
  match(scanner::kFalseKwd);
  fcal::ast::booleanExpr *be = new fcal::ast::booleanExpr(0);
  pr.ast(be);
  return pr;
}

// Expr ::= intConst
ParseResult Parser::parse_int_const() {
  ParseResult pr;
  match(scanner::kIntConst);
  fcal::ast::constExpr *ce = new fcal::ast::constExpr(prev_token_->lexeme());
  pr.ast(ce);
  return pr;
}

// Expr ::= floatConst
ParseResult Parser::parse_float_const() {
  ParseResult pr;
  match(scanner::kFloatConst);
  fcal::ast::constExpr *ce = new fcal::ast::constExpr(prev_token_->lexeme());
  pr.ast(ce);
  return pr;
}

// Expr ::= stringConst
ParseResult Parser::parse_string_const() {
  ParseResult pr;
  match(scanner::kStringConst);
  fcal::ast::constExpr *ce = new fcal::ast::constExpr(prev_token_->lexeme());
  pr.ast(ce);
  return pr;
}

// Expr ::= variableName .....
ParseResult Parser::parse_variable_name() {
  ParseResult pr;
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  if (attempt_match(scanner::kLeftSquare)) {
    ParseResult p = parse_expr(0);
    match(scanner::kColon);
    fcal::ast::MatrixExpr *me = new fcal::ast::MatrixExpr(name,
       reinterpret_cast<fcal::ast::Expr*>(p.ast()),
       reinterpret_cast<fcal::ast::Expr*>(parse_expr(0).ast()));
    pr.ast(me);
    match(scanner::kRightSquare);
  }  else if (attempt_match(scanner::kLeftParen)) {
    // Expr ::= varableName '(' Expr ')'
    fcal::ast::nestedExpr *ne = new fcal::ast::nestedExpr(name,
       reinterpret_cast<fcal::ast::Expr*>(parse_expr(0).ast()));
    pr.ast(ne);
    match(scanner::kRightParen);
  } else {
    // variable
    fcal::ast::varExpr *ve = new fcal::ast::varExpr(name);
    pr.ast(ve);
  }
  return pr;
}

// Expr ::= leftParen Expr rightParen
ParseResult Parser::parse_nested_expr() {
  ParseResult pr;
  bool k = false;
  std::string name;
  if (attempt_match(scanner::kVariableName)) {
      name = prev_token_->lexeme();
      k = true;
  }
  match(scanner::kLeftParen);
  ParseResult e = parse_expr(0);
  match(scanner::kRightParen);
  if (k) {
      fcal::ast::nestedExpr *n = new fcal::ast::nestedExpr(name,
         reinterpret_cast<fcal::ast::Expr*>(e.ast()));
      pr.ast(n);
  } else {
      fcal::ast::functionCallExpr *n = new fcal::ast::functionCallExpr(
        reinterpret_cast<fcal::ast::Expr*>(e.ast()));
      pr.ast(n);
  }
  return pr;
}

// Expr ::= 'if' Expr 'then' Expr 'else' Expr
ParseResult Parser::parse_if_expr() {
  ParseResult pr;

  match(scanner::kIfKwd);
  ParseResult e1 = parse_expr(0);
  match(scanner::kThenKwd);
  ParseResult e2 = parse_expr(0);
  match(scanner::kElseKwd);
  ParseResult e3 = parse_expr(0);
  fcal::ast::ifExpr *i = new fcal::ast::ifExpr(
    reinterpret_cast<fcal::ast::Expr*>(e1.ast()),
    reinterpret_cast<fcal::ast::Expr*>(e2.ast()),
    reinterpret_cast<fcal::ast::Expr*>(e3.ast()));
  pr.ast(i);
  return pr;
}

// Expr ::= 'let' Stmts 'in' Expr 'end'
ParseResult Parser::parse_let_expr() {
  ParseResult pr;
  match(scanner::kLetKwd);
  ParseResult s = parse_stmts();
  match(scanner::kInKwd);
  ParseResult e = parse_expr(0);
  match(scanner::kEndKwd);
  fcal::ast::letExpr *l = new fcal::ast::letExpr(
    reinterpret_cast<fcal::ast::Stmts*>(s.ast()),
    reinterpret_cast<fcal::ast::Expr*>(e.ast()));
  pr.ast(l);
  return pr;
}

// Expr ::= '!' Expr
ParseResult Parser::parse_not_expr() {
  ParseResult pr;
  match(scanner::kNotOp);
  ParseResult n = parse_expr(0);
  fcal::ast::notExpr *n1 = new fcal::ast::notExpr(
    reinterpret_cast<fcal::ast::Expr*>(n.ast()));
  pr.ast(n1);
  return pr;
}
// Expr ::= Expr plusSign Expr
ParseResult Parser::parse_addition(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  match(scanner::kPlusSign);
  ParseResult a = parse_expr(prev_token_->lbp());
  fcal::ast::plusExpr *p = new fcal::ast::plusExpr(
    reinterpret_cast<fcal::ast::Expr*>(prLeft.ast()),
    reinterpret_cast<fcal::ast::Expr*>(a.ast()));
  pr.ast(p);
  return pr;
}

// Expr ::= Expr star Expr
ParseResult Parser::parse_multiplication(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  match(scanner::kStar);
  ParseResult m = parse_expr(prev_token_->lbp());
  fcal::ast::mulExpr *m1 = new fcal::ast::mulExpr (
    reinterpret_cast<fcal::ast::Expr*>(prLeft.ast()),
    reinterpret_cast<fcal::ast::Expr*>(m.ast()));
  pr.ast(m1);
  return pr;
}

// Expr ::= Expr dash Expr
ParseResult Parser::parse_subtraction(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  match(scanner::kDash);
  ParseResult s = parse_expr(prev_token_->lbp());
  fcal::ast::minusExpr *s1 = new fcal::ast::minusExpr (
    reinterpret_cast<fcal::ast::Expr*>(prLeft.ast()),
    reinterpret_cast<fcal::ast::Expr*>(s.ast()));
  pr.ast(s1);
  return pr;
}

// Expr ::= Expr forwardSlash Expr
ParseResult Parser::parse_division(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  match(scanner::kForwardSlash);
  ParseResult d1 = parse_expr(prev_token_->lbp());
  fcal::ast::divExpr *d = new fcal::ast::divExpr (
    reinterpret_cast<fcal::ast::Expr*>(prLeft.ast()),
    reinterpret_cast<fcal::ast::Expr*>(d1.ast()));
  pr.ast(d);
  return pr;
}


// Expr ::= Expr equalEquals Expr ==
// Expr ::= Expr lessThanEquals Expr <=
// Expr ::= Expr greaterThanEquals Expr >=
// Expr ::= Expr notEquals Expr !=
// Expr ::= Expr leftAngle Expr <
// Expr ::= Expr rightAngle Expr >
/* Notice that for relational operators we use just one parse
   function.  This shows another possible means for implementing
   expressions, as opposed to the method used for arithmetic
   expressions in which each operation has its own parse method.  It
   will depend on what we do in iteration 3 in building an abstract
   syntax tree to decide which method is better.
*/
ParseResult Parser::parse_relational_expr(ParseResult prLeft) {
  // parser has already matched left expression
  ParseResult pr;

  next_token();
  // just advance token, since examining it in parse_expr caused
  // this method being called.
  std::string op = prev_token_->lexeme();

  fcal::ast::relationshipExpr *re = new fcal::ast::relationshipExpr(
    reinterpret_cast<fcal::ast::Expr*>(prLeft.ast()), op,
    reinterpret_cast<fcal::ast::Expr*>(parse_expr(prev_token_->lbp()).ast()));
  pr.ast(re);
  return pr;
}

// Helper function used by the parser.

void Parser::match(const scanner::TokenType &tt) {
  if (!attempt_match(tt)) {
    throw(make_error_msg_expected(tt));
  }
}

bool Parser::attempt_match(const scanner::TokenType &tt) {
  if (curr_token_->terminal() == tt) {
    next_token();
    return true;
  }
  return false;
}

bool Parser::next_is(const scanner::TokenType &tt) {
  return curr_token_->terminal() == tt;
}

void Parser::next_token() {
  if (curr_token_ == NULL) {
    throw(std::string(
        "Internal Error: should not call nextToken in unitialized state"));
  } else if (curr_token_->terminal() == scanner::kEndOfFile &&
           curr_token_->next() == NULL) {
    prev_token_ = curr_token_;
  } else if (curr_token_->terminal() != scanner::kEndOfFile &&
             curr_token_->next() == NULL) {
    throw(make_error_msg("Error: tokens end with endOfFile"));
  } else {
    prev_token_ = curr_token_;
    curr_token_ = curr_token_->next();
  }
}

std::string Parser::terminal_description(const scanner::TokenType &terminal) {
  scanner::Token *dummy_token = new scanner::Token();
  dummy_token->setTerminal(terminal);
  dummy_token->setLexeme("");
  dummy_token->setNext(NULL);
  scanner::ExtToken *dummy_ext_token = new scanner::ExtToken(this, dummy_token);
  dummy_ext_token->ExtendToken(this, dummy_token);
  std::string s = dummy_ext_token->description();
  delete dummy_token;
  delete dummy_ext_token;
  return s;
}

std::string Parser::make_error_msg_expected(
    const scanner::TokenType &terminal) {
  std::string s = (std::string) "Expected " + std::to_string(terminal) +
                  " but found " + curr_token_->description();
  return s;
}

std::string Parser::make_error_msg(const scanner::TokenType &terminal) {
  std::string s = "Unexpected symbol " + terminal_description(terminal);
  return s;
}

std::string Parser::make_error_msg(const char *msg) { return msg; }

} /* namespace parser */
} /* namespace fcal */
