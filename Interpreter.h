/*
Dallin Henderson
Interpreter.h
Project 4: Rule Evaluation
*/
#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <iostream>
#include <vector>
#include <string>
#include "Database.h"
#include "Header.h"
#include "Relation.h"
#include "Tuple.h"

using namespace std;

class Interpreter {
public:
	Interpreter() {}
	Interpreter(DatalogProgram* program) {
		datalogProgram = program;
		database = new Database(datalogProgram);
		evaluateRules();
		evaluateQueries();
	}
	void evaluateRules() {
		cout << "Rule Evaluation" << endl;
		
		//Fixed-point algorithm
		int n = 0;
		bool changed;
		do {
			n++;
			changed = false;

			

			//For each rule, evaluate each predicate, natural join all resulting relations, and project rule's HP columns onto the joined relation
			for (unsigned int i = 0; i < datalogProgram->getRuleVec().size(); i++) {
				Relation* firstR;
				vector<Relation*> rCollection;
				Rule currentRule = datalogProgram->getRuleVec().at(i);
				//Evaluate rule's first predicate and add resulting relation 'r' to collection
				firstR = evaluatePredicate(currentRule.getPredicate());
				//Evaluate each predicate in rule's predicate list and add resulting relations to collection
				for (unsigned int j = 0; j < currentRule.getPredList().size(); j++) {
					rCollection.push_back(evaluatePredicate(currentRule.getPredList().at(j)));
				}
				//Join collection elements into one relation, 'f1'
				Relation* f1 = firstR;
				for (unsigned int j = 0; j < rCollection.size(); j++) {
					f1 = f1->naturalJoin2(rCollection.at(j));
				}
 				//Project columns of rule's head predicate onto f1, 'f2'
				vector<string> ids;
				HeadPredicate* hp = currentRule.getHP();
				ids.push_back(hp->getFirstVar());
				vector<string> hp_varList = hp->getVars();
				for (unsigned int j = 0; j < hp_varList.size(); j++) {
					ids.push_back(hp_varList.at(j));
				}
				Relation* f2 = f1->project(ids); 

				//Rename f2's attributes to match rDB's attributes, 'f3'
				Relation rDB = database->getRelation(hp->getID());
				Header hDB = rDB.getHeader();
				vector<string> hDBattributes = hDB.getAttributes();
				Relation* f3 = f2;
				for (unsigned int j = 0; j < hDBattributes.size(); j++) {
					f3 = f3->rename(j, hDBattributes.at(j));
				}
				//Join f3 with rDB, update rDB with this new relation
				Relation rDBupdate;
				if (rDBupdate.getRows().size() > 0) {
					rDBupdate = *rDB.naturalJoin2(f3);
				}
				else {
					rDBupdate = *f3;
				}
				//Print the current rule, insert new Tuples into current relation and print those that are new			
				set<Tuple> newRows = rDBupdate.getRows();
				vector<string> rDBHeaderVals = rDBupdate.getHeader().getAttributes();
				cout << currentRule.toString() << endl;
				for (Tuple T : newRows) {
					bool thisChanged = false;
					bool newT = database->getRelation(hp->getID()).addTuple(T);
					if (newT) {
						changed = true;
						thisChanged = true;
					}
					if (thisChanged) {
						vector<string> Tvals = T.getVals();
						cout << "  ";
						for (unsigned int j = 0; j < Tvals.size(); j++) {
							cout << rDBHeaderVals.at(j) + '=' + Tvals.at(j);
							if ((j + 1) != Tvals.size()) {
								cout << ", ";
							}
						}
						cout << endl;
					}
				}
			}
		} while (changed);
		
		cout << endl << "Schemes populated after " << n << " passes through the Rules." << endl << endl;
	}
	void evaluateQueries() {
		for (unsigned int i = 0; i < datalogProgram->getQueryVec().size(); i++) {
			newRelations.push_back(evaluatePredicate(datalogProgram->getQueryVec().at(i)));
		}
		cout << "Query Evaluation" << endl;
		for (unsigned int i = 0; i < newRelations.size(); i++) {		//for each query-created relation

			if (!newRelations.at(i)->getRows().empty()) {				//if there are rows in the relation
				cout << datalogProgram->getQueryVec().at(i)->toString() << "? Yes(" << newRelations.at(i)->getRows().size() << ')' << endl;
				if (newRelations.at(i)->hasIDS()) {
					cout << newRelations.at(i)->toString();
				}
			}
			else {
				cout << datalogProgram->getQueryVec().at(i)->toString() << "? No" << endl;
			}
		}
	}
	Relation* evaluatePredicate(Predicate* query) {
		map<string, Relation> rMap = database->getRelations();
		string newName = query->getID();				//Name from query to match with scheme
		Header newHeader;								//Placeholder header for newRelation constructor
		Relation* newRelation = new Relation(newName, newHeader);			//New relation created from query 
		Relation rMatch = rMap[newName];				//Matched scheme
		set<Tuple> rows = rMatch.getRows();				//Rows of matched scheme
		vector<int> projections;						//Index vector, stores which header and tuple indices to project at the end
		vector<string> IDs;								//ID vector, keeps track of known ID's
		vector<string> IDVals;

		newRelation->setHeader(rMatch.getHeader());		//Copy matched scheme header to newRelation header
		newRelation->setRows(rMatch.getRows());			//Copy all tuples from matched scheme to newRelation
		//Operate on param1
		//if param1 is const, sellect all tuples matching param1 val at index 0
		if (query->getParam1()->toString()[0] == '\'') {
			//Select tuple if matches index 0 matches param1 val 
			newRelation = newRelation->select(0, -1, query->getParam1()->toString());
		}
		//else, param1 is ID, store index and ID to project later
		else {
			projections.push_back(0);
			IDs.push_back(query->getParam1()->toString());
			newRelation = newRelation->rename(0, query->getParam1()->toString());
			newRelation->tripHasIDs();
		}
		//Operate on parameterList
		for (unsigned int i = 0; i < query->getParameterList().size(); i++) {
			//if parameter is const, sellect for tuples whose index i+1 matches parameter val
			if (query->getParameterList().at(i)->toString()[0] == '\'') {
				newRelation = newRelation->select(i + 1, -1, query->getParameterList().at(i)->toString());
			}
			//else, parameter is ID
			else {
				int IDIndex = -1;
				//search for ID in ID vector
				for (unsigned int j = 0; j < IDs.size(); j++) {

					//Parameter val was found in ID vector
					if (IDs.at(j) == query->getParameterList().at(i)->toString()) {
						IDIndex = j;
					}
				}
				//if ID not found, new ID, store index and ID to match and project later
				if (IDIndex == -1) {
					projections.push_back(i + 1);
					IDs.push_back(query->getParameterList().at(i)->toString());
					newRelation = newRelation->rename(i + 1, query->getParameterList().at(i)->toString());
					newRelation->tripHasIDs();
				}
				//else, ID found, ID is dublicate, select rows where current index and stored indices relating to ID match
				else {
					newRelation = newRelation->select(i + 1, IDIndex);
				}
			}
		}
		//If there were ID's in the query, make final projections
		if (newRelation->hasIDS()) {
			newRelation = newRelation->project(projections, IDs);
		}

		return newRelation;
	}
private:
	DatalogProgram* datalogProgram;
	Database* database;
	vector<Relation*> newRelations;
};

#endif