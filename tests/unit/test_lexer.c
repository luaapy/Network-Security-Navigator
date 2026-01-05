#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nsn.h"
#include "core/token.h"

// Declaration from lexer.c (if not in a public header yet)
// In a real build, we'd include "Parser/lexer.h" or similar.
// Since Nsn_Tokenize is in lexer.c and we have no header for it specifically 
// (other than what we might have put in nsn_internal or manually), 
// we declare it here.
NsnToken* Nsn_Tokenize(const char *source);

int tests_passed = 0;
int tests_failed = 0;

void assert_token(NsnToken token, NsnTokenKind expected_kind, const char* expected_text) {
    if (token.kind != expected_kind) {
        printf("FAIL: Expected kind %s, got %s\n", 
               NsnToken_KindName(expected_kind), NsnToken_KindName(token.kind));
        tests_failed++;
        return;
    }
    
    if (expected_text) {
        if (token.length != (int)strlen(expected_text) || 
            strncmp(token.start, expected_text, token.length) != 0) {
            printf("FAIL: Expected text '%.*s', got '%.*s'\n", 
                   (int)strlen(expected_text), expected_text, 
                   token.length, token.start);
            tests_failed++;
            return;
        }
    }
    tests_passed++;
}

void test_simple_print() {
    printf("Test: print \"hello\"\n");
    const char *source = "print \"hello\"";
    NsnToken *tokens = Nsn_Tokenize(source);
    
    assert_token(tokens[0], NSN_TOK_PRINT, "print");
    assert_token(tokens[1], NSN_TOK_STRING, "\"hello\"");
    assert_token(tokens[2], NSN_TOK_EOF, NULL);
    
    free(tokens);
}

void test_numbers() {
    printf("Test: Numbers (int, float, ip)\n");
    const char *source = "42 3.14 192.168.1.1";
    NsnToken *tokens = Nsn_Tokenize(source);
    
    assert_token(tokens[0], NSN_TOK_INT, "42");
    assert_token(tokens[1], NSN_TOK_FLOAT, "3.14");
    assert_token(tokens[2], NSN_TOK_IP, "192.168.1.1");
    assert_token(tokens[3], NSN_TOK_EOF, NULL);
    
    free(tokens);
}

void test_keywords() {
    printf("Test: Keywords\n");
    const char *source = "if else func return while for";
    NsnToken *tokens = Nsn_Tokenize(source);
    
    assert_token(tokens[0], NSN_TOK_IF, "if");
    assert_token(tokens[1], NSN_TOK_ELSE, "else");
    assert_token(tokens[2], NSN_TOK_FUNC, "func");
    assert_token(tokens[3], NSN_TOK_RETURN, "return");
    assert_token(tokens[4], NSN_TOK_WHILE, "while");
    assert_token(tokens[5], NSN_TOK_FOR, "for");
    assert_token(tokens[6], NSN_TOK_EOF, NULL);
    
    free(tokens);
}

void test_operators() {
    printf("Test: Operators\n");
    const char *source = "+ - * / == !=";
    NsnToken *tokens = Nsn_Tokenize(source);
    
    assert_token(tokens[0], NSN_TOK_PLUS, "+");
    assert_token(tokens[1], NSN_TOK_MINUS, "-");
    assert_token(tokens[2], NSN_TOK_STAR, "*");
    assert_token(tokens[3], NSN_TOK_SLASH, "/");
    assert_token(tokens[4], NSN_TOK_EQ_EQ, "==");
    assert_token(tokens[5], NSN_TOK_BANG_EQ, "!=");
    assert_token(tokens[6], NSN_TOK_EOF, NULL);
    
    free(tokens);
}

int main() {
    printf("Running Lexer Tests...\n");
    
    test_simple_print();
    test_numbers();
    test_keywords();
    test_operators();
    
    printf("\nTests Passed: %d\n", tests_passed);
    printf("Tests Failed: %d\n", tests_failed);
    
    return tests_failed > 0 ? 1 : 0;
}
