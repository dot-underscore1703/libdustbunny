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
	Token *t = malloc(sizeof(Token));

	if(!t) {
		dustbunny_debug("failed to allocate space for token");
		return NULL;
	}
	t->type = type;
	t->value = value ? strdup(value) : NULL;
	return t;
}

/// Destroy the token at the pointer.
void token_destroy(Token *token) {
	dustbunny_debug("destroying token");
	if(!token){
		dustbunny_debug("...but nobody came");
		return;
	};
	free(token->value);
	free(token);
}

/// Get the value of the Token* passed to the function.
char *token_get_value(Token *token) {
	dustbunny_debug("getting token value");
	if(!token){
		dustbunny_debug("...but nobody came");
		return NULL;
	}
	return token->value;
}

/// Get the type of the Token* passed to the function, returns TokenUnknown if the token does not exist.
TokenType token_get_type(Token *token) {
	dustbunny_debug("getting token type");
	if(!token){
		dustbunny_debug("...but nobody came");
		return TokenUnknown;
	}
	return token->type;
}

/// Get the type of the Token* passed to the function as a string. Useful for debugging.
char *token_type_as_str(Token *token){
		dustbunny_debug("getting token type as string");
		switch(token_get_type(token)){
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
