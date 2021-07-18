/*
Dallin Henderson
Parameter.h
Project 4: Rule Evaluation
*/
#ifndef RULE_H
#define RULE_H
#include <iostream>
#include <vector>
#include <set>
#include "Predicate.h"
#include "HeadPredicate.h"

using namespace std;

class Rule {
public:
	//Constructor
	Rule() {}

	//Helper functions
	void setHeadPredicate(HeadPredicate* hPred) {
		headPredicate = hPred;
	}
	void setPredicate(Predicate* pred) {
		predicate = pred;
	}
	void addPredicateList(Predicate* pred) {
		predicateList.push_back(pred);
	}
	HeadPredicate* getHP() {
		return headPredicate;
	}
	Predicate* getPredicate() {
		return predicate;
	}
	vector<Predicate*> getPredList() {
		return predicateList;
	}
	void addTupleString(string newString) {
		newTupleStrings.insert(newString);
	}
	string getTupleStrings() {
		string output;
		for (string S : newTupleStrings) {
			output += S + '\n';
		}
		return output;
	}
	string toString() {
		string output = headPredicate->toString() + " :- " + predicate->toString();
		for (unsigned int i = 0; i < predicateList.size(); i++) {
			output += "," + predicateList.at(i)->toString();
		}
		output += ".";
		return output;
	}
private:
	//Data members
	HeadPredicate* headPredicate;
	Predicate* predicate;
	vector<Predicate*> predicateList;
	set<string> newTupleStrings;
};

#endif