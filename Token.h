/*
Dallin Henderson
Token.h
Project 4: Rule Evaluation
*/
#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>

using namespace std;

enum TokenType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN,
	RIGHT_PAREN, COLON, COLON_DASH,
	MULTIPLY, ADD, SCHEMES, FACTS,
	RULES, QUERIES, ID, STRING, COMMENT,
	UNDEFINED, EndOF
};

string tokenTypeToString(TokenType tokenType) {
	switch (tokenType) {
	case COMMA: return "COMMA"; break;
	case PERIOD: return "PERIOD"; break;
	case Q_MARK: return "Q_MARK"; break;
	case LEFT_PAREN: return "LEFT_PAREN"; break;
	case RIGHT_PAREN: return "RIGHT_PAREN"; break;
	case COLON: return "COLON"; break;
	case COLON_DASH: return "COLON_DASH"; break;
	case MULTIPLY: return "MULTIPLY"; break;
	case ADD: return "ADD"; break;
	case SCHEMES: return "SCHEMES"; break;
	case FACTS: return "FACTS"; break;
	case RULES: return "RULES"; break;
	case QUERIES: return "QUERIES"; break;
	case ID: return "ID"; break;
	case STRING: return "STRING"; break;
	case COMMENT: return "COMMENT"; break;
	case UNDEFINED: return "UNDEFINED"; break;
	case EndOF: return "EOF"; break;
	}
	return "ERROR"; // a string MUST be returned by the end
}


class Token {
public:
	Token(TokenType type, string input, int line) {
		tokenType = type;
		content = input;
		tokenLine = line;
	}
	string content;
	int tokenLine;
	TokenType tokenType;
	string toString() {
		string tokenStr = "(" + tokenTypeToString(tokenType) + ",\"" + content + "\"," + to_string(tokenLine) + ")";
		return tokenStr;
	}
	string tttoStr() {
		return tokenTypeToString(tokenType);
	}
};

#endif