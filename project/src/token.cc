/*******************************************************************************
 * Name            : token.cc
 * Project         : fcal
 * Module          : scanner
 * Description     : This file provides the Token linked list class for
 *					 scanner.cc
 * Copyright       : 2017 Original Authors. All rights reserved.
 * Original Authors : Dalton Stokke, Xukun Qin
 * Modifications by : none
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "include/token.h"
#include "include/scanner.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Functions
 ******************************************************************************/

// Token constructors
/*
 Token::Token(Token terminal, std::string Lexeme, Token *next){
	terminal_ = terminal;
	lexeme = Lexeme;
	next_ = next;
}

 Token::Token(Token *next){
	next_ = next;
 }
*/
Token::Token() {}

// Token deconstructor
Token::~Token() {}

// Token selectors
void Token::setTerminal(TokenType terminal) {
    terminal_ = terminal;
}
void Token::setLexeme(std::string Lexeme) {
    lexeme_ = Lexeme;
}
void Token::setNext(Token *next) {
    next_ = next;
}
int Token::hasNext() {
    if (next_ != nullptr) {
        return TRUE;
    } else {
        return FALSE;
    }
}

} /* namespace scanner */
} /* namespace fcal */
