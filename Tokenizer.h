/*
Dallin Henderson
Tokenizer.h
Project 4: Rule Evaluation
*/
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <cctype>
#include <vector>
#include "Token.h"

using namespace std;

class Tokenizer {
public:
	vector<Token*> tokens;

	void getNextToken(string type, int tokenLine) { //Known chars
		TokenType tType;
		if (type == "COMMA") {
			//cout << "COMMA" << endl;
			tType = COMMA;
			Token* newToken = new Token(tType, ",", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "PERIOD") {
			//cout << "PERIOD" << endl;
			tType = PERIOD;
			Token* newToken = new Token(tType, ".", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "Q_MARK") {
			//cout << "Q_MARK" << endl;
			tType = Q_MARK;
			Token* newToken = new Token(tType, "?", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "LEFT_PAREN") {
			//cout << "LEFT_PAREN" << endl;
			tType = LEFT_PAREN;
			Token* newToken = new Token(tType, "(", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "RIGHT_PAREN") {
			//cout << "RIGHT_PAREN" << endl;
			tType = RIGHT_PAREN;
			Token* newToken = new Token(tType, ")", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "COLON") {
			//cout << "COLON" << endl;
			tType = COLON;
			Token* newToken = new Token(tType, ":", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "COLON_DASH") {
			//cout << "COLON_DASH" << endl;
			tType = COLON_DASH;
			Token* newToken = new Token(tType, ":-", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "MULTIPLY") {
			//cout << "MULTIPLY" << endl;
			tType = MULTIPLY;
			Token* newToken = new Token(tType, "*", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "ADD") {
			//cout << "ADD" << endl;
			tType = ADD;
			Token* newToken = new Token(tType, "+", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "SCHEMES") {
			//cout << "SCHEMES" << endl;
			tType = SCHEMES;
			Token* newToken = new Token(tType, "Schemes", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "FACTS") {
			//cout << "FACTS" << endl;
			tType = FACTS;
			Token* newToken = new Token(tType, "Facts", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "RULES") {
			//cout << "RULES" << endl;
			tType = RULES;
			Token* newToken = new Token(tType, "Rules", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "QUERIES") {
			//cout << "QUERIES" << endl;
			tType = QUERIES;
			Token* newToken = new Token(tType, "Queries", tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "EofF") {
			//cout << "EofF" << endl;
			tType = EndOF;
			Token* newToken = new Token(tType, "", tokenLine);
			tokens.push_back(newToken);
		}
	}
	void getNextToken(string type, string str, int tokenLine) {
		TokenType tType;
		if (type == "ID") {
			//cout << "ID: " << str << endl;
			tType = ID;
			Token* newToken = new Token(tType, str, tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "STRING") {
			//cout << "STRING:" << str << endl;
			tType = STRING;
			Token* newToken = new Token(tType, str, tokenLine);
			tokens.push_back(newToken);
		}
		else if (type == "COMMENT") {
			//No comments will be output
		}
		else if (type == "UNDEFINED") {
			//cout << "UNDEFINED:" << str << endl;
			tType = UNDEFINED;
			Token* newToken = new Token(tType, str, tokenLine);
			tokens.push_back(newToken);
		}
	}
	void getNextToken(string type, char str, int tokenLine) {
		TokenType tType;
		if (type == "UNDEFINED") {
			//cout << "UNDEFINED: " << str << endl;
			tType = UNDEFINED;
			string newStr = "";
			newStr += str;
			Token* newToken = new Token(tType, newStr, tokenLine);
			tokens.push_back(newToken);
		}
	}

	vector<Token*> sendTokens() {
		return tokens;
	}
};
#endif