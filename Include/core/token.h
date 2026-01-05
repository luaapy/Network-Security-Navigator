/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Token definitions
 */

#ifndef NSN_CORE_TOKEN_H
#define NSN_CORE_TOKEN_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    /* Special */
    NSN_TOK_EOF = 0,
    NSN_TOK_ERROR,

    /* Literals */
    NSN_TOK_IDENTIFIER,
    NSN_TOK_STRING,
    NSN_TOK_INT,
    NSN_TOK_FLOAT,
    NSN_TOK_IP,       // 192.168.1.1
    NSN_TOK_NETWORK,  // 192.168.1.0/24

    /* Keywords */
    NSN_TOK_FUNC,
    NSN_TOK_VAR,
    NSN_TOK_RETURN,
    NSN_TOK_IF,
    NSN_TOK_ELSE,
    NSN_TOK_FOR,
    NSN_TOK_WHILE,
    NSN_TOK_IN,
    NSN_TOK_PRINT,
    NSN_TOK_SCAN,
    NSN_TOK_PING,
    NSN_TOK_DISCOVER, 
    NSN_TOK_TRUE,
    NSN_TOK_FALSE,
    NSN_TOK_NULL,
    NSN_TOK_IMPORT,
    NSN_TOK_TRY,
    NSN_TOK_CATCH,

    /* Operators & Delimiters */
    NSN_TOK_PLUS,     // +
    NSN_TOK_MINUS,    // -
    NSN_TOK_STAR,     // *
    NSN_TOK_SLASH,    // /
    NSN_TOK_PERCENT,  // %
    NSN_TOK_EQUAL,    // =
    NSN_TOK_EQ_EQ,    // ==
    NSN_TOK_BANG,     // !
    NSN_TOK_BANG_EQ,  // !=
    NSN_TOK_LESS,     // <
    NSN_TOK_LESS_EQ,  // <=
    NSN_TOK_GREATER,  // >
    NSN_TOK_GREATER_EQ, // >=
    NSN_TOK_COLON,    // :
    NSN_TOK_COMMA,    // ,
    NSN_TOK_DOT,      // .
    NSN_TOK_LPAREN,   // (
    NSN_TOK_RPAREN,   // )
    NSN_TOK_LBRACE,   // {
    NSN_TOK_RBRACE,   // }
    NSN_TOK_LBRACKET, // [
    NSN_TOK_RBRACKET, // ]
    NSN_TOK_ARROW,    // ->

} nsn_token_kind;

typedef struct {
    nsn_token_kind kind;
    const char *start;
    int length;
    int line;
    int column;
} nsn_token;

const char* NsnToken_KindName(nsn_token_kind kind);

#ifdef __cplusplus
}
#endif

#endif // NSN_CORE_TOKEN_H
