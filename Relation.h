/*
Dallin Henderson
Relation.h
Project 4: Rule Evaluation
*/
#ifndef RELATION_H
#define RELATION_H
#include <iostream>
#include <vector>
#include <set>
#include "Tuple.h"
#include "DatalogProgram.h"

using namespace std;

class Relation {
public:
	Relation() {}
	Relation(string newName, Header newHeader) {
		name = newName;
		header = newHeader;
	}
	bool  addTuple(Tuple row) {
		bool changed = rows.insert(row).second;
		return changed;
	}
	void setName(string val) {
		name = val;
	}
	void setHeader(Parameter* param1, vector<Parameter*> parameterList) {
		header.addAttribute(param1->toString());
		for (unsigned int i = 0; i < parameterList.size(); i++) {
			header.addAttribute(parameterList.at(i)->toString());
		}
	}
	void setHeader(Header newHeader) {
		header = newHeader;
	}
	void addToHeader(string newName) {
		header.addAttribute(newName);
	}
	void setRows(set<Tuple> tuples) {
		rows = tuples;
	}
	void tripHasIDs() {
		hasIDs = true;
	}
	void tripChanged() {
		changed = true;
	}
	string getName() {
		return name;
	}
	Header getHeader() {
		return header;
	}
	Relation* select(const int checkIndex, const int matchIndex = -1, const string matchString = "") {
		set<Tuple> newRows;

		if (matchIndex > -1) {		//Index needs to match a prior index in Tuple
			for (Tuple T : rows) {
				vector<string> currentRow = T.getVals();
				if (currentRow.at(checkIndex) == currentRow.at(matchIndex)) {
					newRows.insert(T);
				}
			}
		}
		else {						//Index needs to match string provided
			for (Tuple T : rows) {
				vector<string> currentRow = T.getVals();
				if (currentRow.at(checkIndex) == matchString) {
					newRows.insert(T);
				}
			}
		}
		rows = newRows;

		return this;
	}
	Relation* project(vector<int> projections, vector<string> IDs) {
		//CANNOT CHANGE COLUMN ORDER
		
		bool hErased = false;
		set<Tuple> newSet;
		for (Tuple T : rows) {				//erase columns not in the projection (indices not found in keepVec)
			Tuple newRow;
			for (int i = T.getSize() - 1; i > -1; i--) {				//for each index in the tuple, starting at the last
				bool indexNotFound = true;
				for (unsigned int j = 0; j < projections.size(); j++) {				//Search for current index j in keepVec
					if (i == projections.at(j)) {
						indexNotFound = false;
					}
				}
				if (indexNotFound) {		//current index not in keepVec, erase it
					T.erase(i);
					if (!hErased) {
						header.erase(i);
					}
				}
			}
			hErased = true;
			newRow = T;
			newSet.insert(newRow);
		}
		rows = newSet;
		return this;
	}
	Relation* project(vector<string> IDs) {
		//CAN CHANGE COLUMN ORDER
		
		vector<string> headerVals = header.getAttributes();
		set<Tuple> newRows;
		//Create new order vector
		vector<int> orderVec;
		for (unsigned int i = 0; i < IDs.size(); i++) {
			for (unsigned int j = 0; j < headerVals.size(); j++) {
				if (headerVals.at(j) == IDs.at(i)) {
					orderVec.push_back(j);
					break;
				}
			}
		}
		//Create new header with projected var order
		Header newHeader;
		for (unsigned int i = 0; i < orderVec.size(); i++) {
			newHeader.addAttribute(headerVals.at(orderVec.at(i)));
		}
		header = newHeader;
		//Create and insert new tuples
		for (Tuple T : rows){
			Tuple newT;
			for (unsigned int i = 0; i < orderVec.size(); i++) {
				newT.addVal(T.getVals().at(orderVec.at(i)));
			}
			newRows.insert(newT);
		}
		//Set rows to newRows
		rows = newRows;

		return this;
	}
	Relation* rename(int index, string newVar) {
		header.rename(index, newVar);
		return this;
	}
	Relation* naturalJoin(Relation* relation2) {
		Header newHeader = header;
		vector<string> attributes1 = header.getAttributes();
		Header header2 = relation2->getHeader();
		vector<string> attributes2 = header2.getAttributes();

		
		//Find matching header indices
		vector<int> header1matches;
		vector<int> header2matches;
		for (unsigned int i = 0; i < attributes1.size(); i++) {
			for (unsigned int j = 0; j < attributes2.size(); j++) {
				if (attributes1.at(i) == attributes2.at(j)) {
					header1matches.push_back(i);
					header2matches.push_back(j);
				}
			}
		}
		//Combine headers
		for (unsigned int i = 0; i < attributes2.size(); i++) {
			newHeader.addAttribute(attributes2.at(i));
		}

		set<Tuple> rows2 = relation2->getRows();

		//If tuple 1 or 2 have matching data at header match spots, combine both tuples into a new tuple and insert new tuple into new relation 
		Relation* r = new Relation("r",newHeader);
		for (Tuple t1 : rows) {
			vector<string> values1 = t1.getVals();
			for (Tuple t2 : rows2) {
				vector<string> values2 = t2.getVals();
				for (unsigned int i = 0; i < header1matches.size(); i++) {
					if (values1.at(header1matches.at(i)) == values2.at(header2matches.at(i))) {
						Tuple newTuple;
						for (unsigned int j = 0; j < values1.size(); j++) {
							newTuple.addVal(values1.at(j));
						}
						for (unsigned int j = 0; j < values2.size(); j++) {
							newTuple.addVal(values2.at(j));
						}
						r->addTuple(newTuple);
					}
				}
			}
			/*
			//If no new Tuples were created, simply splice original Tuples into new Tuple and insert into new relation
			if (r->getRows().size() == 0) {
				Tuple newTuple;
				for (unsigned int i = 0; i < ; i++) {

				}
				for (unsigned int i = 0; i < ; i++) {

				}
				r->addTuple(newTuple);
			}
			*/
		}
		return r;
	}
	Relation* naturalJoin2(Relation* relation2) {
		Header newHeader = header;
		vector<string> attributes1 = header.getAttributes();
		Header header2 = relation2->getHeader();
		vector<string> attributes2 = header2.getAttributes();

		//Find matching header indices
		vector<int> header1matches;
		vector<int> header2matches;
		for (unsigned int i = 0; i < attributes1.size(); i++) {
			for (unsigned int j = 0; j < attributes2.size(); j++) {
				if (attributes1.at(i) == attributes2.at(j)) {
					header1matches.push_back(i);
					header2matches.push_back(j);
				}
			}
		}
		//Combine headers
		for (unsigned int i = 0; i < attributes2.size(); i++) {
			newHeader.addAttribute(attributes2.at(i));
		}

		set<Tuple> rows2 = relation2->getRows();

		//If tuples 1 and 2 are joinable, combine both tuples into a new tuple and insert new tuple into new relation
		//Else, if not new tuples were created, combine all tuples (all possible combos)
		Relation* r = new Relation("r", newHeader);
		if (header1matches.size() > 0) {
			for (Tuple t1 : rows) {
				vector<string> values1 = t1.getVals();
				for (Tuple t2 : rows2) {
					vector<string> values2 = t2.getVals();
					if (joinable(header1matches, t1, header2matches, t2)) {
						Tuple newTuple;
						for (unsigned int j = 0; j < values1.size(); j++) {
							newTuple.addVal(values1.at(j));
						}
						for (unsigned int j = 0; j < values2.size(); j++) {
							newTuple.addVal(values2.at(j));
						}
						r->addTuple(newTuple);
					}
				}
			}
		}
		//If there were no matching header attributes, cartesian product r1 and r2 Tuples and insert into new relation
		else {
			for (Tuple t1 : rows) {
				vector<string> values1 = t1.getVals();
				for (Tuple t2 : rows2) {
					vector<string> values2 = t2.getVals();
					Tuple newTuple;
					for (unsigned int j = 0; j < values1.size(); j++) {
						newTuple.addVal(values1.at(j));
					}
					for (unsigned int j = 0; j < values2.size(); j++) {
						newTuple.addVal(values2.at(j));
					}
					r->addTuple(newTuple);
				}
			}
		}
		return r;
	}
	bool joinable(vector<int> matches1, Tuple t1, vector<int> matches2, Tuple t2) {
		vector<string> tv1 = t1.getVals();
		vector<string> tv2 = t2.getVals();
		bool areJoinable = true;
		for (unsigned int i = 0; i < matches1.size(); i++) {
			if (tv1.at(matches1.at(i)) != tv2.at(matches2.at(i))){
				areJoinable = false;
			}
		}
		if (matches1.size() == 0) {
			areJoinable = false;
		}
		return areJoinable;
	}
	set<Tuple> getRows() {
		return rows;
	}
	bool hasIDS() {
		return hasIDs;
	}
	string toString() {
		string output;
		set<Tuple>::iterator it;
		for (it = rows.begin(); it != rows.end(); it++) {		//for each tuple
			output += "  ";
			for (int j = 0; j < it->getSize(); j++) {			//for each index in the tuple
				output += header.getAttributes().at(j) + '=' + it->getVals().at(j);
				if (j + 1 != it->getSize()) {
					output += ", ";
				}
			}
			output += '\n';
		}
		return output;
	}
private:
	string name;
	Header header;
	set<Tuple> rows;
	bool hasIDs = false;
	bool changed = false;
};

#endif