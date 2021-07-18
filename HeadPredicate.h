/*
Dallin Henderson
HeadPredicate.h
Project 4: Rule Evaluation
*/
#ifndef HEADPREDICATE_H
#define HEADPREDICATE_H
#include <iostream>
#include <vector>
#include "Parameter.h"

using namespace std;

class HeadPredicate {
public:
	//Constructor
	HeadPredicate() {}

	//Helper Functions
	void setID(string id) {
		ID = id;
	}
	void setFirst(string frst) {
		first = frst;
	}
	void addString(string add) {
		IDs.push_back(add);
	}

	string toString() {
		string output = ID + "(" + first;
		for (unsigned int i = 0; i < IDs.size(); i++) {
			output += "," + IDs.at(i);
		}
		output += ")";
		return output;
	}
	string getID() {
		return ID;
	}
	string getFirstVar() {
		return first;
	}
	vector<string> getVars() {
		return IDs;
	}

private:
	//Data Members
	string ID;
	string first;
	vector<string> IDs;
};

#endif