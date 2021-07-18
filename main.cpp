/*
Dallin Henderson
main.cpp
Lab 4 - Rule Evaluation
*/
#include <iostream>
#include <fstream>
#include <vector>
#include "Lexer.h"
#include "DatalogProgram.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {

	string fileName = argv[1];

	Lexer* myLexer = new Lexer(fileName);

	DatalogProgram* myDatalogProgram = new DatalogProgram(myLexer->start());

	Interpreter* myInterpreter = new Interpreter(myDatalogProgram);


	//Deallocate memory
	delete myLexer;
	delete myDatalogProgram;
	delete myInterpreter;

	system("pause");

	return 0;
}
