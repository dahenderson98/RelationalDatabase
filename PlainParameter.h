/*
Dallin Henderson
PlainParameter.h
Project 4: Rule Evaluation
*/
#ifndef PLAINPARAMETER_H
#define PLAINPARAMETER_H
#include <iostream>
#include <vector>
#include "Parameter.h"

using namespace std;

class PlainParameter : public Parameter {
public:
	PlainParameter() {};
	void setID(string id) {
		ID = id;
	}
	string getID() {
		return ID;
	}
	string toString() {
		return ID;
	}
private:
	string ID;
};

#endif