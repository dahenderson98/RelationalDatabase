/*
Dallin Henderson
Expression.h
Project 4: Rule Evaluation
*/
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <vector>
#include "Parameter.h"

using namespace std;

class Expression : public Parameter {
public:
	Expression() {}

	//Helper functions
	void setMembers(Parameter* param1, string oper, Parameter* param2) {
		p1 = param1;
		op = oper;
		p2 = param2;
	}
	void set1(Parameter* param1) {
		p1 = param1;
	}
	void setOp(string oper) {
		op = oper;
	}
	void set2(Parameter* param2) {
		p2 = param2;
	}
	string toString() {
		string output;
		output += "(";
		output += p1->toString();
		output += op;
		output += p2->toString();
		output += ")";
		return output;
	}

private:
	Parameter* p1;
	string op;
	Parameter* p2;
};

#endif