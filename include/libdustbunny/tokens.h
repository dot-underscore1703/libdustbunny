#ifndef TOKENS_H
#define TOKENS_H

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


#endif
