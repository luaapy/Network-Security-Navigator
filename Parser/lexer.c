/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Lexical analyzer implementation
 */

#include "nsn.h"
#include "core/token.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    const char *start;
    const char *current;
    int line;
    int column_start;
} Lexer;

static Lexer lexer;

static void initLexer(const char *source) {
    lexer.start = source;
    lexer.current = source;
    lexer.line = 1;
    lexer.column_start = 0;
}

static int isAtEnd() {
    return *lexer.current == '\0';
}

static char advance() {
    lexer.current++;
    return lexer.current[-1];
}

static char peek() {
    return *lexer.current;
}

static char peekNext() {
    if (isAtEnd()) return '\0';
    return lexer.current[1];
}

static int match(char expected) {
    if (isAtEnd()) return 0;
    if (*lexer.current != expected) return 0;
    lexer.current++;
    return 1;
}

static NsnToken makeToken(NsnTokenKind kind) {
    NsnToken token;
    token.kind = kind;
    token.start = lexer.start;
    token.length = (int)(lexer.current - lexer.start);
    token.line = lexer.line;
    // Calculation of column is approximate here for simplicity
    token.column = (int)(lexer.start - (lexer.current - token.length)); 
    return token;
}

static NsnToken errorToken(const char *message) {
    NsnToken token;
    token.kind = NSN_TOK_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = lexer.line;
    return token;
}

static void skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                lexer.line++;
                advance();
                break;
            case '#':
                while (peek() != '\n' && !isAtEnd()) advance();
                break;
            default:
                return;
        }
    }
}

static NsnTokenKind checkKeyword(int start, int length, const char *rest, NsnTokenKind type) {
    if (lexer.current - lexer.start == start + length &&
        memcmp(lexer.start + start, rest, length) == 0) {
        return type;
    }
    return NSN_TOK_IDENTIFIER;
}

static NsnTokenKind identifierType() {
    switch (lexer.start[0]) {
        case 'c': return checkKeyword(1, 4, "atch", NSN_TOK_CATCH);
        case 'e': return checkKeyword(1, 3, "lse", NSN_TOK_ELSE);
        case 'f':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'a': return checkKeyword(2, 3, "lse", NSN_TOK_FALSE);
                    case 'o': return checkKeyword(2, 1, "r", NSN_TOK_FOR);
                    case 'u': return checkKeyword(2, 2, "nc", NSN_TOK_FUNC);
                }
            }
            break;
        case 'i': return checkKeyword(1, 1, "f", NSN_TOK_IF);
        case 'n': return checkKeyword(1, 3, "ull", NSN_TOK_NULL);
        case 'p':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'i': return checkKeyword(2, 2, "ng", NSN_TOK_PING);
                    case 'r': return checkKeyword(2, 3, "int", NSN_TOK_PRINT);
                }
            }
            break;
        case 'r': return checkKeyword(1, 5, "eturn", NSN_TOK_RETURN);
        case 's': return checkKeyword(1, 3, "can", NSN_TOK_SCAN);
        case 't':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'r':
                        if (lexer.current - lexer.start > 2) {
                            switch (lexer.start[2]) {
                                case 'u': return checkKeyword(3, 1, "e", NSN_TOK_TRUE);
                                case 'y': return checkKeyword(3, 0, "", NSN_TOK_TRY);
                            }
                        }
                        break;
                }
            }
            break;
        case 'w': return checkKeyword(1, 4, "hile", NSN_TOK_WHILE);
    }
    return NSN_TOK_IDENTIFIER;
}

static NsnToken identifier() {
    while (isalnum(peek()) || peek() == '_') advance();
    return makeToken(identifierType());
}

static NsnToken number() {
    while (isdigit(peek())) advance();

    // Look for fractional part or IP address dot
    if (peek() == '.' && isdigit(peekNext())) {
        // Could be float or IP
        // For simplicity in Phase 1, if we see 3 dots it's IP, else float?
        // Or handle IP parsing later.
        // Let's assume standard float for now, will refine for IP.
        advance();
        while (isdigit(peek())) advance();
        
        // Check for further dots for IP address: 192.168.1.1
        if (peek() == '.') {
             advance();
             while (isdigit(peek())) advance();
             if (peek() == '.') {
                 advance();
                 while (isdigit(peek())) advance();
                 return makeToken(NSN_TOK_IP);
             }
        } else {
             return makeToken(NSN_TOK_FLOAT);
        }
    }

    return makeToken(NSN_TOK_INT);
}

static NsnToken string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') lexer.line++;
        advance();
    }

    if (isAtEnd()) return errorToken("Unterminated string.");

    // The closing quote
    advance();
    return makeToken(NSN_TOK_STRING);
}

static NsnToken scanToken() {
    skipWhitespace();
    lexer.start = lexer.current;

    if (isAtEnd()) return makeToken(NSN_TOK_EOF);

    char c = advance();

    if (isalpha(c)) return identifier();
    if (isdigit(c)) return number();

    switch (c) {
        case '(': return makeToken(NSN_TOK_LPAREN);
        case ')': return makeToken(NSN_TOK_RPAREN);
        case '{': return makeToken(NSN_TOK_LBRACE);
        case '}': return makeToken(NSN_TOK_RBRACE);
        case '[': return makeToken(NSN_TOK_LBRACKET);
        case ']': return makeToken(NSN_TOK_RBRACKET);
        case ',': return makeToken(NSN_TOK_COMMA);
        case '.': return makeToken(NSN_TOK_DOT);
        case '-': 
            return match('>') ? makeToken(NSN_TOK_ARROW) : makeToken(NSN_TOK_MINUS);
        case '+': return makeToken(NSN_TOK_PLUS);
        case ';': return makeToken(NSN_TOK_EOF); // Treat semicolon as end for now? Or ignore
        case '*': return makeToken(NSN_TOK_STAR);
        case '!':
            return match('=') ? makeToken(NSN_TOK_BANG_EQ) : makeToken(NSN_TOK_BANG);
        case '=':
            return match('=') ? makeToken(NSN_TOK_EQ_EQ) : makeToken(NSN_TOK_EQUAL);
        case '<':
            return match('=') ? makeToken(NSN_TOK_LESS_EQ) : makeToken(NSN_TOK_LESS);
        case '>':
            return match('=') ? makeToken(NSN_TOK_GREATER_EQ) : makeToken(NSN_TOK_GREATER);
        case '/':
            // Comments are handled in skipWhitespace, so this is division
            return makeToken(NSN_TOK_SLASH);
        case '"': return string();
    }

    return errorToken("Unexpected character.");
}

// Helper to get string representation of kind
const char* NsnToken_KindName(NsnTokenKind kind) {
    switch (kind) {
        case NSN_TOK_EOF: return "EOF";
        case NSN_TOK_ERROR: return "ERROR";
        case NSN_TOK_IDENTIFIER: return "IDENTIFIER";
        case NSN_TOK_STRING: return "STRING";
        case NSN_TOK_INT: return "INT";
        case NSN_TOK_FLOAT: return "FLOAT";
        case NSN_TOK_IP: return "IP";
        case NSN_TOK_FUNC: return "FUNC";
        case NSN_TOK_PRINT: return "PRINT";
        case NSN_TOK_LPAREN: return "LPAREN";
        case NSN_TOK_RPAREN: return "RPAREN";
        default: return "UNKNOWN";
    }
}

// Public API
// Returns a dynamically allocated array of tokens, terminated by EOF token
// Caller must free.
NsnToken* Nsn_Tokenize(const char *source) {
    initLexer(source);
    
    int capacity = 8;
    int count = 0;
    NsnToken* tokens = (NsnToken*)malloc(sizeof(NsnToken) * capacity);
    
    for (;;) {
        NsnToken token = scanToken();
        if (count + 1 >= capacity) {
            capacity *= 2;
            tokens = (NsnToken*)realloc(tokens, sizeof(NsnToken) * capacity);
        }
        tokens[count++] = token;
        if (token.kind == NSN_TOK_EOF) break;
    }
    
    return tokens;
}
