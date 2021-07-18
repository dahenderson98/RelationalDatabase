/*
Dallin Henderson
Predicate.h
Project 4: Rule Evaluation
*/
#ifndef PREDICATE_H
#define PREDICATE_H
#include <iostream>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate {
public:
	//Constructor
	Predicate() {}

	//Helper Functions
	void setType(string tpe) {
		type = tpe;
	}
	void setID(string id) {
		ID = id;
	}
	void setFirst(Parameter* param) {
		param1 = param;
	}
	void addString(Parameter* add) {
		parameterList.push_back(add);
	}
	string getID() {
		return ID;
	}
	Parameter* getParam1() {
		return param1;
	}
	vector<Parameter*> getParameterList() {
		return parameterList;
	}
	string toString() {
		string output = ID + "(" + param1->toString();
		for (unsigned int i = 0; i < parameterList.size(); i++) {
			output += "," + parameterList.at(i)->toString();
		}
		output += ")";
		return output;
	}

private:
	//Data members
	string type;				//can be scheme, fact or query
	string ID;
	Parameter* param1;
	vector<Parameter*> parameterList;
};

#endif