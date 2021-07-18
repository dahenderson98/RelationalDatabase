/*
Dallin Henderson
Tuple.h
Project 4: Rule Evaluation
*/
#ifndef TUPLE_H
#define TUPLE_H
#include <iostream>
#include <vector>

using namespace std;

class Tuple {
public:
	void addVals(Parameter* param1, vector<Parameter*> parameterList) {
		values.push_back(param1->toString());
		for (unsigned int i = 0; i < parameterList.size(); i++) {
			values.push_back(parameterList.at(i)->toString());
		}
	}
	void addVal(string newStr) {
		values.push_back(newStr);
	}
	int getSize() const {
		return values.size();
	}
	vector<string> getVals() const {
		return values;
	}
	bool operator< (const Tuple & other) const {
		return values < other.values;
	}
	void erase(int index) {
		values.erase(values.begin() + index);
	}
	int getSize() {
		return values.size();
	}
	string toString() const {
		string output;
		for (unsigned int i = 0; i < values.size(); i++) {
			output += values.at(i) + '\t';
		}
		return output;
	}
private:
	vector<string> values;
};

#endif