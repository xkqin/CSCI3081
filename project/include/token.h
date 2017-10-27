/*******************************************************************************
 * Name            : token.h
 * Project         : fcal
 * Module          : scanner
 * Description     : Header file for token.cc
 * Copyright       : 2017 Original Authors. All rights reserved.
 * Original Authors : Dalton Stokke, Xukun Qin
 * Modifications by : none
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_TOKEN_H_
#define PROJECT_INCLUDE_TOKEN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string>

#define TRUE 1
#define FALSE 0

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
/* below are the possible terminal types for each token */

  enum kTokenEnumType {
     /*0*/ kIntKwd,
     kFloatKwd,
     kBoolKwd,
     kTrueKwd,
     kFalseKwd,
     /*5*/kStringKwd,
     kMatrixKwd,
     kLetKwd,
     kInKwd,
     kEndKwd,
     /*10*/ kIfKwd,
     kThenKwd,
     kElseKwd,
     kRepeatKwd,
     kWhileKwd,
     kPrintKwd,
     kToKwd,

     // Constants
     /*17*/ kIntConst,
     kFloatConst,
     kStringConst,

     // Names
     /*20*/ kVariableName,

     // Punctuation
     /*21*/ kLeftParen,
     kRightParen,
     kLeftCurly,
     kRightCurly,
     /*25*/ kLeftSquare,
     kRightSquare,

     kSemiColon,
     kColon,

     // Operators
     /*29*/ kAssign,
     kPlusSign,
     kStar,
     kDash,
     kForwardSlash,
     /*34*/ kLessThan,
     kLessThanEqual,
     kGreaterThan,
     kGreaterThanEqual,
     /*38*/ kEqualsEquals,
     kNotEquals,
     /*40*/ kAndOp,
     kOrOp,
     kNotOp,

     // Special terminal types
     /*43*/ kEndOfFile,
     kLexicalError     // DO NOT MOVE, ARRAYSIZE dependency
};

typedef enum kTokenEnumType TokenType;

class Token {
 public:
    // Token(TokenType, std::string, Token*);
    // Token(Token*);
    Token();
    ~Token();
    void setTerminal(TokenType);
    void setLexeme(std::string);
    void setNext(Token*);
    int hasNext();
    TokenType terminal() {return terminal_;}
    std::string lexeme() {return lexeme_;}
    Token* next() {return next_;}

		/* optional getters and setters:
		 * void setLexemeLength(int Lexeme_Length);
		 * void setLexemeLine(int Lexeme_Line);
		 * void setLexemeColumn(int Lexeme_Column);
		 * int getLexemeLength(){return lexeme_length;}
		 * int getLexemeLine(){return lexeme_line;}
		 * int getLexemeColumn(){return lexeme_column;}
		 */
 private:
    TokenType terminal_;
    std::string lexeme_;
    Token* next_;

		/* optional fields:
		 * int lexeme_length;
		 * int lexeme_line;
		 * int lexeme_column
		 */
}; /* Token class */

} /* namespace scanner */
} /* namespace fcal */


#endif  // PROJECT_INCLUDE_TOKEN_H_
