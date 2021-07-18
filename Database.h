/*
Dallin Henderson
Database.h
Project 4 Rule Evaluation
*/
#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <vector>
#include <map>
#include "Header.h"
#include "Relation.h"
#include "Tuple.h"

using namespace std;

class Database {
public:
	Database(DatalogProgram* dp) {
		datalogProgram = dp;
		schemesVec = datalogProgram->getSchemeVec();
		factsVec = datalogProgram->getFactVec();
		rulesVec = datalogProgram->getRuleVec();

		schemesEval();
		factsEval();
		queriesEval();
	}
	void schemesEval() {
		for (unsigned int i = 0; i < schemesVec.size(); i++) {
			Header newHeader;
			newHeader.addAttribute(schemesVec.at(i)->getParam1()->toString());
			for (unsigned int j = 0; j < schemesVec.at(i)->getParameterList().size(); j++) {
				newHeader.addAttribute(schemesVec.at(i)->getParameterList().at(j)->toString());
			}
			Relation relation(schemesVec.at(i)->getID(), newHeader);
			relations.insert({ relation.getName(), relation });
		}
	}
	void factsEval() {
		for (unsigned int i = 0; i < factsVec.size(); i++) {
			Tuple newRow;
			newRow.addVals(factsVec.at(i)->getParam1(), factsVec.at(i)->getParameterList());
			relations[factsVec.at(i)->getID()].addTuple(newRow);
		}
	}
	void queriesEval() {
		//interpreter.evaluate(relations, datalogProgram->getQueryVec());
	}
	map<string, Relation> getRelations() {
		return relations;
	}
	Relation& getRelation(string rName) {
		return relations[rName];
	}
	void updateRelation(string rName, Relation newR) {
		relations[rName] = newR;
	}
private:
	DatalogProgram* datalogProgram;
	vector<Predicate*> schemesVec;
	vector<Predicate*> factsVec;
	vector<Rule> rulesVec;
	map<string, Relation> relations;
};

#endif