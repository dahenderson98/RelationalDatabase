/*
Dallin Henderson
Lexer.h
Project 4: Rule Evaluation
*/
#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include "Tokenizer.h"

using namespace std;

class Lexer {
public:
	Lexer(string fileName) {
		fileContents.open(fileName);
		if (!fileContents.is_open()) {
			cout << "Could not open file" << endl;
		}
	}
	ifstream fileContents;
	Tokenizer tokenizer;
	int currentLine = 1;
	vector<Token*> tokens;

	vector<Token*> start() {
		if (!fileContents.is_open()) {
			return tokens;
		}
		char c;

		do {									//Start reading chars
			int linesAdvanced = 0;
			fileContents.get(c);
			if (fileContents.eof()) {	// EOF
				c = EOF;
				tokenizer.getNextToken("EofF", currentLine);
				break;
			}
			else if (isspace(c)) {
				if (c == '\n') {				//Newline means update current line
					currentLine++;
				}
				else {
					//Do nothing, skip character
				}
			}
			else {
				bool inString = true;
				string str = "";

				switch (c) {
				case ',':			//COMMA
					tokenizer.getNextToken("COMMA", currentLine);
					break;
				case '.':			//PERIOD
					tokenizer.getNextToken("PERIOD", currentLine);
					break;
				case '?':			//Q_MARK
					tokenizer.getNextToken("Q_MARK", currentLine);
					break;
				case '(':			//LEFT_PAREN
					tokenizer.getNextToken("LEFT_PAREN", currentLine);
					break;
				case ')':			//RIGHT_PAREN
					tokenizer.getNextToken("RIGHT_PAREN", currentLine);
					break;
				case ':':			//COLON or COLON_DASH
					if (fileContents.peek() == '-') {
						fileContents.get(c);
						tokenizer.getNextToken("COLON_DASH", currentLine);
					}
					else {
						tokenizer.getNextToken("COLON", currentLine);
					}
					break;
				case '*':			//MULTIPLY
					tokenizer.getNextToken("MULTIPLY", currentLine);
					break;
				case '+':			//ADD
					tokenizer.getNextToken("ADD", currentLine);
					break;
				case 'S':			//SCHEMES
					if (fileContents.peek() == 'c') {
						fileContents.get(c);
						if (fileContents.peek() == 'h') {
							fileContents.get(c);
							if (fileContents.peek() == 'e') {
								fileContents.get(c);
								if (fileContents.peek() == 'm') {
									fileContents.get(c);
									if (fileContents.peek() == 'e') {
										fileContents.get(c);
										if (fileContents.peek() == 's') {
											fileContents.get(c);
											if (!isalnum(fileContents.peek())) {		//next char is whitespace
												tokenizer.getNextToken("SCHEMES", currentLine);
											}
											else {									//next char is not whitespace
												fileContents.get(c);
												string id = "Schemes";
												id += c;
												while (isalnum(fileContents.peek())) {	//next char is not whitespace
													fileContents.get(c);
													id += c;
												}	//peeked nonalnum
												tokenizer.getNextToken("ID", id, currentLine);
											}
										}
										else if (isspace(fileContents.peek())) {
											fileContents.get(c);
											tokenizer.getNextToken("ID", "Scheme", currentLine);
											if (c == '\n') {
												currentLine++;
											}
										}
										else if (isalnum(fileContents.peek())) {
											fileContents.get(c);
											string id = "Scheme";
											id += c;
											while (isalnum(fileContents.peek())) {
												fileContents.get(c);
												id += c;
											}
											tokenizer.getNextToken("ID", id, currentLine);
										}
									}
									else if (isspace(fileContents.peek())) {
										fileContents.get(c);
										tokenizer.getNextToken("ID", "Schem", currentLine);
										if (c == '\n') {
											currentLine++;
										}
									}
									else if (isalnum(fileContents.peek())) {
										fileContents.get(c);
										string id = "Schem";
										id += c;
										while (isalnum(fileContents.peek())) {
											fileContents.get(c);
											id += c;
										}
										tokenizer.getNextToken("ID", id, currentLine);
									}
								}
								else if (isspace(fileContents.peek())) {
									fileContents.get(c);
									tokenizer.getNextToken("ID", "Sche", currentLine);
									if (c == '\n') {
										currentLine++;
									}
								}
								else if (isalnum(fileContents.peek())) {
									fileContents.get(c);
									string id = "Sche";
									id += c;
									while (isalnum(fileContents.peek())) {
										fileContents.get(c);
										id += c;
									}
									tokenizer.getNextToken("ID", id, currentLine);
								}
							}
							else if (isspace(fileContents.peek())) {
								fileContents.get(c);
								tokenizer.getNextToken("ID", "Sch", currentLine);
								if (c == '\n') {
									currentLine++;
								}
							}
							else if (isalnum(fileContents.peek())) {
								fileContents.get(c);
								string id = "Sch";
								id += c;
								while (isalnum(fileContents.peek())) {
									fileContents.get(c);
									id += c;
								}
								tokenizer.getNextToken("ID", id, currentLine);
							}
						}
						else if (isspace(fileContents.peek())) {
							fileContents.get(c);
							tokenizer.getNextToken("ID", "Sc", currentLine);
							if (c == '\n') {
								currentLine++;
							}
						}
						else if (isalnum(fileContents.peek())) {
							fileContents.get(c);
							string id = "Sc";
							id += c;
							while (isalnum(fileContents.peek())) {
								fileContents.get(c);
								id += c;
							}
							tokenizer.getNextToken("ID", id, currentLine);
						}
					}
					else if (isalnum(fileContents.peek())) {
						fileContents.get(c);
						string id = "S";
						id += c;
						while (isalnum(fileContents.peek())) {
							fileContents.get(c);
							id += c;
						}
						tokenizer.getNextToken("ID", id, currentLine);
					}
					else {
						tokenizer.getNextToken("ID", "S", currentLine);
					}
					break;
				case 'F':			//FACTS
					if (fileContents.peek() == 'a') {
						fileContents.get(c);
						if (fileContents.peek() == 'c') {
							fileContents.get(c);
							if (fileContents.peek() == 't') {
								fileContents.get(c);
								if (fileContents.peek() == 's') {
									fileContents.get(c);
									if (!isalnum(fileContents.peek())) {		//next char is whitespace
										tokenizer.getNextToken("FACTS", currentLine);
									}
									else {									//next char is not whitespace
										fileContents.get(c);
										string id = "Facts";
										id += c;
										while (isalnum(fileContents.peek())) {	//next char is not whitespace
											fileContents.get(c);
											id += c;
										}	//peeked notalnum
										tokenizer.getNextToken("ID", id, currentLine);
									}
								}
								else if (isspace(fileContents.peek())) {
									fileContents.get(c);
									tokenizer.getNextToken("ID", "Fact", currentLine);
									if (c == '\n') {
										currentLine++;
									}
								}
								else if (isalnum(fileContents.peek())) {
									fileContents.get(c);
									string id = "Fact";
									id += c;
									while (isalnum(fileContents.peek())) {
										fileContents.get(c);
										id += c;
									}
									tokenizer.getNextToken("ID", id, currentLine);
								}
							}
							else if (isspace(fileContents.peek())) {
								fileContents.get(c);
								tokenizer.getNextToken("ID", "Fac", currentLine);
								if (c == '\n') {
									currentLine++;
								}
							}
							else if (isalnum(fileContents.peek())) {
								fileContents.get(c);
								string id = "Fac";
								id += c;
								while (isalnum(fileContents.peek())) {
									fileContents.get(c);
									id += c;
								}
								tokenizer.getNextToken("ID", id, currentLine);
							}
						}
						else if (isspace(fileContents.peek())) {
							fileContents.get(c);
							tokenizer.getNextToken("ID", "Fa", currentLine);
							if (c == '\n') {
								currentLine++;
							}
						}
						else if (isalnum(fileContents.peek())) {
							fileContents.get(c);
							string id = "Fa";
							id += c;
							while (isalnum(fileContents.peek())) {
								fileContents.get(c);
								id += c;
							}
							tokenizer.getNextToken("ID", id, currentLine);
						}
					}
					else if (isalnum(fileContents.peek())) {
						fileContents.get(c);
						string id = "F";
						id += c;
						while (isalnum(fileContents.peek())) {
							fileContents.get(c);
							id += c;
						}
						tokenizer.getNextToken("ID", id, currentLine);
					}
					else {
						tokenizer.getNextToken("ID", "F", currentLine);
					}
					break;
				case 'R':			//RULES
					if (fileContents.peek() == 'u') {
						fileContents.get(c);
						if (fileContents.peek() == 'l') {
							fileContents.get(c);
							if (fileContents.peek() == 'e') {
								fileContents.get(c);
								if (fileContents.peek() == 's') {
									fileContents.get(c);
									if (!isalnum(fileContents.peek())) {		//next char is whitespace
										tokenizer.getNextToken("RULES", currentLine);
									}
									else {									//next char is not whitespace
										fileContents.get(c);
										string id = "Rules";
										id += c;
										while (isalnum(fileContents.peek())) {	//next char is not whitespace
											fileContents.get(c);
											id += c;
										}	//peeked nonalnum
										tokenizer.getNextToken("ID", id, currentLine);
									}
								}
								else if (isspace(fileContents.peek())) {
									fileContents.get(c);
									tokenizer.getNextToken("ID", "Rule", currentLine);
									if (c == '\n') {
										currentLine++;
									}
								}
								else if (isalnum(fileContents.peek())) {
									fileContents.get(c);
									string id = "Rule";
									id += c;
									while (isalnum(fileContents.peek())) {
										fileContents.get(c);
										id += c;
									}
									tokenizer.getNextToken("ID", id, currentLine);
								}
							}
							else if (isspace(fileContents.peek())) {
								fileContents.get(c);
								tokenizer.getNextToken("ID", "Rul", currentLine);
								if (c == '\n') {
									currentLine++;
								}
							}
							else if (isalnum(fileContents.peek())) {
								fileContents.get(c);
								string id = "Rul";
								id += c;
								while (isalnum(fileContents.peek())) {
									fileContents.get(c);
									id += c;
								}
								tokenizer.getNextToken("ID", id, currentLine);
							}
						}
						else if (isspace(fileContents.peek())) {
							fileContents.get(c);
							tokenizer.getNextToken("ID", "Ru", currentLine);
							if (c == '\n') {
								currentLine++;
							}
						}
						else if (isalnum(fileContents.peek())) {
							fileContents.get(c);
							string id = "Ru";
							id += c;
							while (isalnum(fileContents.peek())) {
								fileContents.get(c);
								id += c;
							}
							tokenizer.getNextToken("ID", id, currentLine);
						}
					}
					else if (isalnum(fileContents.peek())) {
						fileContents.get(c);
						string id = "R";
						id += c;
						while (isalnum(fileContents.peek())) {
							fileContents.get(c);
							id += c;
						}
						tokenizer.getNextToken("ID", id, currentLine);
					}
					else {
						tokenizer.getNextToken("ID", "R", currentLine);
					}
					break;
				case 'Q':			//QUERIES
					if (fileContents.peek() == 'u') {
						fileContents.get(c);
						if (fileContents.peek() == 'e') {
							fileContents.get(c);
							if (fileContents.peek() == 'r') {
								fileContents.get(c);
								if (fileContents.peek() == 'i') {
									fileContents.get(c);
									if (fileContents.peek() == 'e') {
										fileContents.get(c);
										if (fileContents.peek() == 's') {
											fileContents.get(c);
											if (!isalnum(fileContents.peek())) {		//next char is whitespace
												tokenizer.getNextToken("QUERIES", currentLine);
											}
											else {									//next char is not whitespace
												fileContents.get(c);
												string id = "Queries";
												id += c;
												while (isalnum(fileContents.peek())) {	//next char is not whitespace
													fileContents.get(c);
													id += c;
												}	//peeked nonalnum
												tokenizer.getNextToken("ID", id, currentLine);
											}
										}
										else if (isspace(fileContents.peek())) {
											fileContents.get(c);
											tokenizer.getNextToken("ID", "Querie", currentLine);
											if (c == '\n') {
												currentLine++;
											}
										}
										else if (isalnum(fileContents.peek())) {
											fileContents.get(c);
											string id = "Querie";
											id += c;
											while (isalnum(fileContents.peek())) {
												fileContents.get(c);
												id += c;
											}
											tokenizer.getNextToken("ID", id, currentLine);
										}
									}
									else if (isspace(fileContents.peek())) {
										fileContents.get(c);
										tokenizer.getNextToken("ID", "Queri", currentLine);
										if (c == '\n') {
											currentLine++;
										}
									}
									else if (isalnum(fileContents.peek())) {
										fileContents.get(c);
										string id = "Queri";
										id += c;
										while (isalnum(fileContents.peek())) {
											fileContents.get(c);
											id += c;
										}
										tokenizer.getNextToken("ID", id, currentLine);
									}
								}
								else if (isspace(fileContents.peek())) {
									fileContents.get(c);
									tokenizer.getNextToken("ID", "Quer", currentLine);
									if (c == '\n') {
										currentLine++;
									}
								}
								else if (isalnum(fileContents.peek())) {
									fileContents.get(c);
									string id = "Quer";
									id += c;
									while (isalnum(fileContents.peek())) {
										fileContents.get(c);
										id += c;
									}
									tokenizer.getNextToken("ID", id, currentLine);
								}
							}
							else if (isspace(fileContents.peek())) {
								fileContents.get(c);
								tokenizer.getNextToken("ID", "Que", currentLine);
								if (c == '\n') {
									currentLine++;
								}
							}
							else if (isalnum(fileContents.peek())) {
								fileContents.get(c);
								string id = "Que";
								id += c;
								while (isalnum(fileContents.peek())) {
									fileContents.get(c);
									id += c;
								}
								tokenizer.getNextToken("ID", id, currentLine);
							}
						}
						else if (isspace(fileContents.peek())) {
							fileContents.get(c);
							tokenizer.getNextToken("ID", "Qu", currentLine);
							if (c == '\n') {
								currentLine++;
							}
						}
						else if (isalnum(fileContents.peek())) {
							fileContents.get(c);
							string id = "Qu";
							id += c;
							while (isalnum(fileContents.peek())) {
								fileContents.get(c);
								id += c;
							}
							tokenizer.getNextToken("ID", id, currentLine);
						}
					}
					else if (isalnum(fileContents.peek())) {
						fileContents.get(c);
						string id = "Q";
						id += c;
						while (isalnum(fileContents.peek())) {
							fileContents.get(c);
							id += c;
						}
						tokenizer.getNextToken("ID", id, currentLine);
					}
					else {
						tokenizer.getNextToken("ID", "Q", currentLine);
					}
					break;
				case '\'':			//STRING
					str += '\'';
					while (inString) {
						c = fileContents.peek();
						if (c != '\'' && !fileContents.eof()/*c != EOF*/) {
							str += c;
							fileContents.get(c);
							if (c == '\n') {
								linesAdvanced++;
							}
						}
						else if (c == '\'') {	//Found a quote
							fileContents.get(c);
							char d = fileContents.peek();
							if (d != '\'') {	//single closing quote
								inString = false;
								str += '\'';
								tokenizer.getNextToken("STRING", str, currentLine);
								currentLine += linesAdvanced;
							}
							else if (d == '\'') {	//double quotes
								str = str + c + c;
								fileContents.get(c);
							}
						}
						else if (fileContents.eof()) {	//c = EOF
							tokenizer.getNextToken("UNDEFINED", str, currentLine);
							currentLine += linesAdvanced;
							tokenizer.getNextToken("EofF", currentLine);
							inString = false;
						}
					}
					break;
				case '#':			//COMMENT (or block comment, same token)
					str += '#';
					c = fileContents.peek();
					if (c == '|') {	//Block comment
						str += '|';
						fileContents.get(c);
						bool sent = false;
						while (!fileContents.eof()) {
							fileContents.get(c);
							if (c != '|') {		//did not get a pipe
								if (c != '\n') {//did not get a newline
									str += c;
								}
								else {			//got a newline
									if (fileContents.peek() != EOF) { //only append if next char is not EOF
										linesAdvanced++;
										str += c;
									}
								}
							}
							else if (c == '|') {	//found a |, check if next char is #
								str += '|';
								c = fileContents.peek();
								if (c == '#') {		//found closing |#
									fileContents.get(c);
									str += '#';
									tokenizer.getNextToken("COMMENT", str, currentLine);
									currentLine = currentLine + linesAdvanced;
									sent = true;
									break;
								}
								else {				//only found a |
									fileContents.get(c);
									str += c;
								}
							}
						}
						if (!sent) {
							if (c == '\n') {
								str += c;
								linesAdvanced++;
							}
							tokenizer.getNextToken("UNDEFINED", str, currentLine);
							if (c == '\n') {
								linesAdvanced++;
							}
							currentLine += linesAdvanced;
						}
					}
					//else line comment
					else {			//Line comment
						if (c != '\n') { //peeked char is not a newline
							fileContents.get(c);
							str += c;
						}
						else {			//peeked char is a newline
							fileContents.get(c);
							tokenizer.getNextToken("COMMENT", str, currentLine);
							currentLine++;
							break;
						}
						while (!fileContents.eof()) {
							fileContents.get(c);
							if (c != '\n') { //gotten char is not a newline
								str += c;
							}
							else {	//gotten char is a newline
								tokenizer.getNextToken("COMMENT", str, currentLine);
								currentLine++;
								break;
							}
						}
					}
					break;
				default:			//ID or UNDEFINED
					if (isalpha(c)) {
						string id = "";
						id += c;
						while (!isspace(c) && isalnum(c)) {
							c = fileContents.peek();
							if (!isspace(c) && isalnum(c)) {
								fileContents.get(c);
								id += c;
							}
						}
						tokenizer.getNextToken("ID", id, currentLine);
					}
					else {
						tokenizer.getNextToken("UNDEFINED", c, currentLine);
					}
				}
			}
		} while (c != EOF);

		tokens = tokenizer.sendTokens();
		return tokens;
	}
};
#endif