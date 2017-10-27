/*******************************************************************************
 * Name            : scanner.h
 * Project         : fcal
 * Module          : scanner
 * Description     : Header file for scanner module
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_SCANNER_H_
#define PROJECT_INCLUDE_SCANNER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <regex.h>
#include <string>

#include "include/token.h"
#include "include/regex.h"

#define ARRAYSIZE (kLexicalError-1)
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

class Scanner {
 public:
        Scanner();
        Token *Scan(const char *text);
        void print(Token*);
        // Token getToken();
        int Length() {return length;}

        int consume_whitespace_and_comments(regex_t *white_space,
                                regex_t *line_comment, regex_t *block_comment,
                                            const char *text);
 private:
        Token* head;
        Token* current;
        int length;
        regex_t *regexArray[ARRAYSIZE];
        regex_t *line_comment = make_regex("^//[^\n\r]*");
        regex_t *white_space = make_regex("^[\n\t\r ]+");
        regex_t *block_comment = make_regex("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
}; /* Scanner class */

/*******************************************************************************
 * Class Definitions
 *
 * You will need to define a Token class (remember, a pointer of type Token *
 * is returned by the scan method of the scanner class.)
 * Also, Classes are typically declared (and sometimes also defined) in
 * their own header files
 *
 * You will also need to define a Scanner class with a scan and other methods
 ******************************************************************************/

} /* namespace scanner */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_SCANNER_H_
