/*******************************************************************************
 * Name            : scanner.cc
 * Project         : fcal
 * Module          : scanner
 * Description     : file for scanner module
 * Copyright       : 2017 Original Authors. All rights reserved.
 * Original Authors : Dalton Stokke, Xukun Qin
 * Modifications by : none
 ******************************************************************************/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/scanner.h"

// #include <string>
// #include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "include/regex.h"
#include "include/token.h"  // defined Token class


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {


/*******************************************************************************
 * Functions
 ******************************************************************************/
 /*
	TODO:
	- Design pseudo-code. (scanner.cc)
	- Write adequate set of tests (scanner.h)
	- Write code that will pass our tests and provided tests (scanner.cc)
	- document labor in iteration1_work.txt in project directory

	pseudo-code: this class is the defination of the function Token * Scan (const char*)

	1. make regex for every token type
	2. count the number of every regex match the token type
	3. switch to find every token type that we find and link the next to the second token type
	4. return a linked list of the token type

	make regex: */
Scanner::Scanner() {
    regexArray[kIntKwd] = make_regex("^(int){1}");
    regexArray[kFloatKwd] = make_regex("^(float){1}");
    regexArray[kBoolKwd] = make_regex("^((B|b)oolean){1}");
    regexArray[kTrueKwd] = make_regex("^((T|t)rue){1}");
    regexArray[kFalseKwd] = make_regex("^((F|f)alse){1}");
    regexArray[kStringKwd] = make_regex("^(string){1}");
    regexArray[kMatrixKwd] = make_regex("^(M|m)atrix{1}");
    regexArray[kLetKwd] = make_regex("^(let){1}");
    regexArray[kInKwd] = make_regex("^(in){1}");
    regexArray[kEndKwd] = make_regex("^(end){1}");
    regexArray[kIfKwd] = make_regex("^(if){1}");
    regexArray[kThenKwd] = make_regex("^(then){1}");
    regexArray[kElseKwd] = make_regex("^(else){1}");
    regexArray[kRepeatKwd] = make_regex("^(repeat){1}");
    regexArray[kWhileKwd] = make_regex("^(while){1}");
    regexArray[kPrintKwd] = make_regex("^(print){1}");
    regexArray[kToKwd] = make_regex("^(to){1}");
    regexArray[kIntConst] = make_regex("^[0-9]+");
    regexArray[kFloatConst] = make_regex("^[0-9]+\\.[0-9]+");
    regexArray[kStringConst] = make_regex("^\"[^\"]*\"");
    regexArray[kVariableName] = make_regex("^[a-zA-Z_][a-zA-Z_0-9]*");
    regexArray[kLeftParen] = make_regex("^\\(");
    regexArray[kRightParen] = make_regex("^\\)");
    regexArray[kLeftCurly] = make_regex("^\\{");
    regexArray[kRightCurly] = make_regex("^\\}");
    regexArray[kLeftSquare] = make_regex("^\\[");
    regexArray[kRightSquare] = make_regex("^\\]");
    regexArray[kSemiColon] = make_regex("^\\;");
    regexArray[kColon] = make_regex("^\\:");
    regexArray[kAssign] = make_regex("^\\=");
    regexArray[kPlusSign] = make_regex("^\\+");
    regexArray[kStar] = make_regex("^\\*");
    regexArray[kDash] = make_regex("^\\-");
    regexArray[kForwardSlash] = make_regex("^\\/{1}");
    regexArray[kLessThan] = make_regex("^<");
    regexArray[kLessThanEqual] = make_regex("^<=");
    regexArray[kGreaterThan] = make_regex("^>");
    regexArray[kGreaterThanEqual] = make_regex("^>=");
    regexArray[kEqualsEquals] = make_regex("^==");
    regexArray[kNotEquals] = make_regex("^!=");
    regexArray[kAndOp] = make_regex("^\\&\\&");
    regexArray[kOrOp] = make_regex("^\\|\\|");
    regexArray[kNotOp] = make_regex("^\\!");
}

Token* Scanner::Scan(const char* text) {
    TokenType TT;
    current = new Token();
    head = current;

    int num_matched_chars = 0;

    // Consume leading white space and comments
    num_matched_chars =
      consume_whitespace_and_comments(white_space,
                                   line_comment, block_comment, text);
    text = text + num_matched_chars;

    int max_num_matched_chars = 0;

    while (text[0] != '\0') {
        max_num_matched_chars = 0;
        TT = kLexicalError;
        // match the text with every regex that we create
        for (int i = 0; i < ARRAYSIZE; i++) {
            num_matched_chars = match_regex(regexArray[i], text);
                if (num_matched_chars > max_num_matched_chars) {
                max_num_matched_chars = num_matched_chars;
                TT = (TokenType) i;
            }
        }
        // assign the text to its lexeme
        std::string lexeme;
        for (int k = 0; k < max_num_matched_chars; k++) {
            lexeme+= text[k];
        }

        if (TT == kLexicalError) {
            lexeme = text[0];
            text = text+1;
        } else {
            text = text + max_num_matched_chars;
        }
        // Consume white space and comments before trying again for
        // another word or integer.
        num_matched_chars =
           consume_whitespace_and_comments(white_space,
                                   line_comment, block_comment, text);
        text = text + num_matched_chars;

        current->setLexeme(lexeme);  // set lexeme_ to string matched
        current->setTerminal(TT);  // set terminal_ inside that token to TT
        current->setNext(new Token());
        current = current->next();
        length+=1;
        // delete(lexeme);
    }
    current->setLexeme("\0");
    current->setTerminal(kEndOfFile);
    current->setNext(nullptr);
    length+=1;
    return head;
} /* Scan() */

void print(Token* head) {
    while (head != nullptr) {
  // const char *printer = head->lexeme().std::string::c_str();
  std::cout << "lexeme: " << head->lexeme() << " , terminal: "
  << head->terminal() << std::endl;
        // printf("lexeme: %s , terminal: %d ", printer, head->terminal());
        head = head->next();
    }
}

int Scanner::consume_whitespace_and_comments(regex_t *white_space,
                            regex_t *line_comment, regex_t *block_comment,
                                    const char *text) {
    int num_matched_chars = 0;
    int total_num_matched_chars = 0;
    int still_consuming_white_space;

    do {
        still_consuming_white_space = 0;  // exit loop if not reset by a match
        // Try to match line comment
        num_matched_chars = match_regex(line_comment, text);
        total_num_matched_chars += num_matched_chars;
        if (num_matched_chars > 0) {
            text = text + num_matched_chars;
            still_consuming_white_space = 1;
        }

        // Try to match white space
        num_matched_chars = match_regex(white_space, text);
        total_num_matched_chars += num_matched_chars;
        if (num_matched_chars > 0) {
            text = text + num_matched_chars;
            still_consuming_white_space = 1;
        }

        // Try to match block comments
        num_matched_chars = match_regex(block_comment, text);
        total_num_matched_chars += num_matched_chars;
        if (num_matched_chars > 0) {
            text = text + num_matched_chars;
            still_consuming_white_space = 1;
            }
    } while (still_consuming_white_space);

    return total_num_matched_chars;
} /* consume_whitespace_and_comments() */

} /* namespace scanner */
} /* namespace fcal */
