/*
Dallin Henderson
Header.h
Project 4: Rule Evaluation
*/
#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <vector>

using namespace std;

class Header {
public:
	Header() {}
	void addAttribute(string val) {
		attributes.push_back(val);
	}
	vector<string> getAttributes() {
		return attributes;
	}
	void rename(int index, string newName) {
		attributes.at(index) = newName;
	}
	void erase(int i) {
		attributes.erase(attributes.begin() + i);
	}
	string toString() {
		string output;
		for (unsigned int i = 0; i < attributes.size(); i++) {
			output += attributes.at(i) + '\t';
		}
		return output;
	}
private:
	vector<string> attributes;
};

#endif