// ==================================
// TOKENS.C - IM KINDA THE TOKEN TYPE
// ==================================

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libdustbunny/debug.h"

typedef enum { 
	TokenText, 
	TokenNewline, 
	TokenPipe,
	TokenBracketIn,
	TokenBracketOut,
	TokenEquals,
	TokenAmpersand,
	TokenUnknown
} TokenType;

typedef struct Token {
  TokenType type;
  char *value;
} Token;

/// Create new token
Token *token_new(TokenType type, char *value) {
	size_t token_size = sizeof(Token);
	
	dustbunny_debug("creating new token with size of %zu",token_size);
	Token *new_token = malloc(sizeof(Token));

	if(!new_token) {
		dustbunny_debug("failed to allocate space for token");
		return NULL;
	}

	// Token type is important so the parser knows how to use the token when constructing the AST
	new_token->type = type;

	new_token->value = value ? strdup(value) : NULL;
	return new_token;
}

/// Destroy the token at the pointer.
int token_destroy(Token *token) {
	dustbunny_debug("destroying token");
	
	if(!token){
		dustbunny_debug("...but nobody came");
		return 1;
	};

	free(token);
	token = NULL;
	
	return 0;
}

/// Get the type of the Token* passed to the function as a string. Useful for debugging.
char *token_type_as_str(Token *token){
		dustbunny_debug("getting token type as string");
		switch(token->type){
			case TokenText: return "TokenText";
			case TokenNewline: return "TokenNewline";
			case TokenPipe: return "TokenPipe";
			case TokenBracketIn: return "TokenBracketIn";
			case TokenBracketOut: return "TokenBracketOut";
			case TokenEquals: return "TokenEquals";
			case TokenAmpersand: return "TokenAmpersand";
			default: return "TokenUnknown";
		}
		
}
