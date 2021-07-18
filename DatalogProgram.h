/*
Dallin Henderson
DatalogProgram.h
Project 4: Rule Evaluation
*/
#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include "Token.h"
#include "Rule.h"
#include "Predicate.h"
#include "HeadPredicate.h"
#include "Parameter.h"
#include "Expression.h"
#include "PlainParameter.h"

using namespace std;

class DatalogProgram {
public:
	//constructor
	DatalogProgram(vector<Token*> inputVec) {
		tokens = inputVec;
		parse();
	}

	void parse() {
		try {
			if (tokens.at(cursor)->tokenType == SCHEMES) {
				cursor++;
				if (tokens.at(cursor)->tokenType == COLON) {
					cursor++;
					Predicate* newScheme = new Predicate();
					newScheme = scheme();
					schemeVec.push_back(newScheme);
					schemeList();//DONE
					if (tokens.at(cursor)->tokenType == FACTS) {
						cursor++;
						if (tokens.at(cursor)->tokenType == COLON) {
							cursor++;
							factList();//DONE
							if (tokens.at(cursor)->tokenType == RULES) {
								cursor++;
								if (tokens.at(cursor)->tokenType == COLON) {
									cursor++;
									ruleList();//DONE
									if (tokens.at(cursor)->tokenType == QUERIES) {
										cursor++;
										if (tokens.at(cursor)->tokenType == COLON) {
											cursor++;
											query();
											queryList();
											if (tokens.at(cursor)->tokenType == EndOF) {
												//cout << "Success!" << endl;
												//cout << toString();
											}
											else {
												throw tokens.at(cursor);
											}
										}
										else {
											throw tokens.at(cursor);
										}
									}
									else {
										throw tokens.at(cursor);
									}
								}
								else {
									throw tokens.at(cursor);
								}
							}
							else {
								throw tokens.at(cursor);
							}
						}
						else {
							throw tokens.at(cursor);
						}
					}
					else {
						throw tokens.at(cursor);
					}
				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}
		}
		catch (Token* token) {
			cout << "Failure!" << endl << "  " << token->toString() << endl;
		}
	}

	Predicate* scheme() {
		if (tokens.at(cursor)->tokenType == ID) {
			Predicate* newScheme = new Predicate();
			PlainParameter* newParam = new PlainParameter();
			newParam->setID(tokens.at(cursor)->content);
			newScheme->setID(newParam->getID());
			//delete newParam;
			cursor++;
			if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
				cursor++;
				if (tokens.at(cursor)->tokenType == ID) {
					PlainParameter* newParam = new PlainParameter();
					newParam->setID(tokens.at(cursor)->content);
					newScheme->setFirst(newParam);
					//delete newParam;
					cursor++;
					while (tokens.at(cursor)->tokenType == COMMA) {
						cursor++;
						if (tokens.at(cursor)->tokenType == ID) {
							PlainParameter* newParam = new PlainParameter();
							newParam->setID(tokens.at(cursor)->content);
							newScheme->addString(newParam);
						}
						else {
							throw tokens.at(cursor);
						}
						cursor++;
					}
					if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
						cursor++;
						return newScheme;
						//scheme complete
					}
					else {
						throw tokens.at(cursor);
					}
				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}
		}
		else {
			throw tokens.at(cursor);
		}
	}
	void schemeList() {
		if (tokens.at(cursor)->tokenType == ID) {
			Predicate* newScheme = new Predicate();
			newScheme = scheme();
			schemeVec.push_back(newScheme);
			schemeList();							//Recurse schemeList
		}
		else {
			//lambda, schemeList complete
		}
	}
	Predicate* fact() {
		if (tokens.at(cursor)->tokenType == ID) {
			Predicate* newFact = new Predicate();
			newFact->setType("fact");
			newFact->setID(tokens.at(cursor)->content);
			cursor++;
			if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
				cursor++;
				if (tokens.at(cursor)->tokenType == STRING) {
					PlainParameter* newParam = new PlainParameter();
					newParam->setID(tokens.at(cursor)->content);
					domain.insert(tokens.at(cursor)->content);
					newFact->setFirst(newParam);
					cursor++;
					while (tokens.at(cursor)->tokenType == COMMA) {
						cursor++;
						if (tokens.at(cursor)->tokenType == STRING) {
							domain.insert(tokens.at(cursor)->content);
							PlainParameter* newParam = new PlainParameter();
							newParam->setID(tokens.at(cursor)->content);
							newFact->addString(newParam);
						}
						else {
							throw tokens.at(cursor);
						}
						cursor++;
					}
					if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
						cursor++;
						if (tokens.at(cursor)->tokenType == PERIOD) {
							cursor++;
							return newFact;
							//fact complete
						}
						else {
							throw tokens.at(cursor);
						}
					}
					else {
						throw tokens.at(cursor);
					}
				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}
		}
		else {
			throw tokens.at(cursor);
		}
	}
	void factList() {
		if (tokens.at(cursor)->tokenType == ID) {
			Predicate* newFact = new Predicate();
			newFact = fact();
			factVec.push_back(newFact);
			factList();
		}
		else {
			//lambda, factList complete
		}
	}
	Rule* rule() {
		Rule* newRule = new Rule();
		HeadPredicate* newHP = new HeadPredicate();
		//HeadPredicate
		if (tokens.at(cursor)->tokenType == ID) {
			newHP->setID(tokens.at(cursor)->content);
			cursor++;
			if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
				cursor++;
				if (tokens.at(cursor)->tokenType == ID) {
					newHP->setFirst(tokens.at(cursor)->content);
					cursor++;
					while (tokens.at(cursor)->tokenType == COMMA) {
						cursor++;
						if (tokens.at(cursor)->tokenType == ID) {
							newHP->addString(tokens.at(cursor)->content);
						}
						else {
							throw tokens.at(cursor);
						}
						cursor++;
					}
					if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
						newRule->setHeadPredicate(newHP);
						cursor++;
					}
					else {
						throw tokens.at(cursor);
					}
				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}
		}
		//Head predicate complete
		if (tokens.at(cursor)->tokenType == COLON_DASH) {
			cursor++;

			//first predicate (required)
			Predicate* newPr = new Predicate();
			//Param
			if (tokens.at(cursor)->tokenType == ID) {
				newPr->setID(tokens.at(cursor)->content);
				cursor++;
				if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
					cursor++;
					//first param
					if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
						Parameter* newExp = new Expression();
						newExp = parameter();
						newPr->setFirst(newExp);
					}
					else if (tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == STRING) {
						Parameter* newP = new PlainParameter();
						newP = parameter();
						newPr->setFirst(newP);
					}
					cursor++;
					//ParamList
					while (tokens.at(cursor)->tokenType == COMMA) {
						cursor++;
						if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
							Parameter* newExp = new Expression();
							newExp = parameter();
							newPr->addString(newExp);
						}
						else {
							Parameter* newP = new PlainParameter();
							newP = parameter();
							newPr->addString(newP);
						}
						cursor++;
					}
					if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
						newRule->setPredicate(newPr);
						cursor++;
						//predicate complete
					}
					else {
						//throw tokens.at(cursor);
					}

				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}

			//predicate list
			while (tokens.at(cursor)->tokenType == COMMA) {
				cursor++;
				Predicate* newPr = new Predicate();

				//param, predicate list (reqd)
				if (tokens.at(cursor)->tokenType == ID) {	//  ID
					newPr->setID(tokens.at(cursor)->content);
					cursor++;
					if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
						cursor++;
						if (tokens.at(cursor)->tokenType == LEFT_PAREN) {	//first expression
							Parameter* newExp = new Expression();
							newExp = parameter();
							newPr->setFirst(newExp);
						}
						else if (tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == STRING) {	//first plain param
							Parameter* newP = new PlainParameter();
							newP = parameter();
							newPr->setFirst(newP);
						}
						cursor++;

						//param list, predicate list
						while (tokens.at(cursor)->tokenType == COMMA) {
							cursor++;
							if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
								Parameter* newExp = new Expression();
								newExp = parameter();
								newPr->addString(newExp);
							}
							else if (tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == STRING) {
								Parameter* newP = new PlainParameter();
								newP = parameter();
								newPr->addString(newP);
							}
							else {
								throw tokens.at(cursor);
							}
							cursor++;
						}
						if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
							newRule->addPredicateList(newPr);
							cursor++;
							//predicate complete
						}

						else {
							throw tokens.at(cursor);
						}
					}
					else {
						throw tokens.at(cursor);
					}
				}
				else {
					throw tokens.at(cursor);
				}
			}
			if (tokens.at(cursor)->tokenType == PERIOD) {
				cursor++;

				return newRule;
				//rule complete
			}
			else {
				throw tokens.at(cursor);
			}
		}
		else {
			throw tokens.at(cursor);
		}
	}
	void ruleList() {
		if (tokens.at(cursor)->tokenType == ID) {
			Rule* newRule = new Rule();
			newRule = rule();
			ruleVec.push_back(*newRule);
			//cursor++;
			//TokenType toooooo = tokens.at(cursor)->tokenType;
			if (tokens.at(cursor)->tokenType == ID) {
				//cursor++;
				ruleList();
			}
		}
		else {
			//lambda, ruleList complete
		}
	}
	void query() {
		do {
			Predicate* newQuery = new Predicate();
			newQuery->setType("query");
			//Predicate
			//Param
			if (tokens.at(cursor)->tokenType == ID) {
				newQuery->setID(tokens.at(cursor)->content);
				cursor++;
				if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
					cursor++;
					//first param
					if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
						Parameter* newExp = new Expression();
						newExp = parameter();
						newQuery->setFirst(newExp);
					}
					else if (tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == STRING) {
						Parameter* newP = new PlainParameter();
						newP = parameter();
						newQuery->setFirst(newP);
					}
					else {
						throw tokens.at(cursor);
					}
					cursor++;
					//ParamList
					while (tokens.at(cursor)->tokenType == COMMA) {
						cursor++;
						if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
							Parameter* newExp = new Expression();
							newExp = parameter();
							newQuery->addString(newExp);
						}
						else if (tokens.at(cursor)->tokenType == STRING || tokens.at(cursor)->tokenType == ID) {
							Parameter* newP = new PlainParameter();
							newP = parameter();
							newQuery->addString(newP);
						}
						else {
							throw tokens.at(cursor);
						}
						cursor++;
					}
					if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
						cursor++;
						if (tokens.at(cursor)->tokenType == Q_MARK) {
							queryVec.push_back(newQuery);
							cursor++;
							//Query complete
						}
						else {
							throw tokens.at(cursor);
						}
					}
					else {
						throw tokens.at(cursor);
					}

				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}
		} while (tokens.at(cursor)->tokenType == ID);
	}
	void queryList() {
		if (tokens.at(cursor)->tokenType == ID) {
			query();
			queryList();
		}
		else {
			//lambda, queryList complete
		}
	}
	void parameterList() {
		if (tokens.at(cursor)->tokenType == COMMA) {
			cursor++;
			parameter();
			parameterList();
		}
		else {
			//lambda, parameterList complete
		}
	}
	void predicateList() {
		if (tokens.at(cursor)->tokenType == COMMA) {
			cursor++;
			predicate();
			predicateList();
		}
		else {
			//lambda, predicateList complete
		}
	}
	void predicate() {
		if (tokens.at(cursor)->tokenType == ID) {
			cursor++;
			if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
				cursor++;
				parameter();
				parameterList();
				if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
					cursor++;
					//predicate complete
				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}
		}
		else {
			throw tokens.at(cursor);
		}
	}
	void headPredicate() {
		if (tokens.at(cursor)->tokenType == ID) {
			cursor++;
			if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
				cursor++;
				if (tokens.at(cursor)->tokenType == ID) {
					cursor++;
					//idList(); //replace w for loop
					if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
						cursor++;
					}
					else {
						throw tokens.at(cursor);
					}
				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}
		}
		else {
			throw tokens.at(cursor);
		}
	}
	Parameter* parameter() {
		if (tokens.at(cursor)->tokenType == STRING) {
			//cursor++;
			PlainParameter* pParam = new PlainParameter();
			pParam->setID(tokens.at(cursor)->content);
			return pParam;
			//STRING Terminal
		}
		else if (tokens.at(cursor)->tokenType == ID) {
			//cursor++;
			PlainParameter* pParam = new PlainParameter();
			pParam->setID(tokens.at(cursor)->content);
			return pParam;
			//ID Terminal
		}
		else if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
			Expression* exp = new Expression();
			cursor++;
			if (tokens.at(cursor)->tokenType == STRING || tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == LEFT_PAREN) {
				if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
					Expression* param1 = new Expression();
					cursor++;
					if (tokens.at(cursor)->tokenType == STRING || tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == LEFT_PAREN) {
						if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
							param1->set1(expression());
						}
						else {
							PlainParameter* subParam1 = new PlainParameter();
							subParam1->setID(tokens.at(cursor)->content);
							param1->set1(subParam1);
						}
						cursor++;
						if (tokens.at(cursor)->tokenType == ADD || tokens.at(cursor)->tokenType == MULTIPLY) {
							string opr = tokens.at(cursor)->content;
							param1->setOp(opr);
							cursor++;
							if (tokens.at(cursor)->tokenType == STRING || tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == LEFT_PAREN) {
								if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
									param1->set2(expression());
								}
								else {
									PlainParameter* subParam2 = new PlainParameter();
									subParam2->setID(tokens.at(cursor)->content);
									param1->set2(subParam2);
								}
								cursor++;
								if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
									exp->set1(param1);
								}
								else {
									throw tokens.at(cursor);
								}
							}
							else {
								throw tokens.at(cursor);
							}
						}
						else {
							throw tokens.at(cursor);
						}
					}
					else {
						throw tokens.at(cursor);
					}
				}
				else {
					PlainParameter* param1 = new PlainParameter();
					param1->setID(tokens.at(cursor)->content);
					exp->set1(param1);
				}
				cursor++;
				if (tokens.at(cursor)->tokenType == ADD || tokens.at(cursor)->tokenType == MULTIPLY) {
					string opr = tokens.at(cursor)->content;
					exp->setOp(opr);
					cursor++;
					if (tokens.at(cursor)->tokenType == STRING || tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == LEFT_PAREN) {
						if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
							Expression* param2 = new Expression();
							cursor++;
							if (tokens.at(cursor)->tokenType == STRING || tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == LEFT_PAREN) {
								if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
									param2->set1(expression());
								}
								else {
									PlainParameter* subParam1 = new PlainParameter();
									subParam1->setID(tokens.at(cursor)->content);
									param2->set1(subParam1);
								}
								cursor++;
								if (tokens.at(cursor)->tokenType == ADD || tokens.at(cursor)->tokenType == MULTIPLY) {
									string opr = tokens.at(cursor)->content;
									param2->setOp(opr);
									cursor++;
									if (tokens.at(cursor)->tokenType == STRING || tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == LEFT_PAREN) {
										if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
											param2->set2(expression());
										}
										else {
											PlainParameter* subParam2 = new PlainParameter();
											subParam2->setID(tokens.at(cursor)->content);
											param2->set2(subParam2);
										}
										cursor++;
										if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
											exp->set2(param2);
										}
										else {
											throw tokens.at(cursor);
										}
									}
									else {
										throw tokens.at(cursor);
									}
								}
								else {
									throw tokens.at(cursor);
								}
							}
							else {
								throw tokens.at(cursor);
							}
						}
						else {
							PlainParameter* param2 = new PlainParameter();
							param2->setID(tokens.at(cursor)->content);
							exp->set2(param2);
						}
						cursor++;
						//exp->setMembers(param1, opr, param2);
						return exp;
					}
					else {
						throw tokens.at(cursor);
					}
				}
				else {
					throw tokens.at(cursor);
				}
			}
			else {
				throw tokens.at(cursor);
			}
		}
		else {
			throw tokens.at(cursor);
		}
	}
	Expression* expression() {
		if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
			Expression* expr = new Expression();
			cursor++;
			//first param
			if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
				expr->set1(expression());
			}
			else if (tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == STRING) {
				PlainParameter* param1 = new PlainParameter();
				param1->setID(tokens.at(cursor)->content);
				expr->set1(param1);
			}
			else {
				throw tokens.at(cursor);
			}
			cursor++;
			//operator
			if (tokens.at(cursor)->tokenType == ADD || tokens.at(cursor)->tokenType == MULTIPLY) {
				string opr = tokens.at(cursor)->content;
				expr->setOp(opr);

			}
			else {
				throw tokens.at(cursor);
			}
			cursor++;
			//second param
			if (tokens.at(cursor)->tokenType == LEFT_PAREN) {
				expr->set2(expression());
			}
			else if (tokens.at(cursor)->tokenType == ID || tokens.at(cursor)->tokenType == STRING) {
				PlainParameter* param2 = new PlainParameter();
				param2->setID(tokens.at(cursor)->content);
				expr->set2(param2);
			}
			else {
				throw tokens.at(cursor);
			}
			cursor++;
			if (tokens.at(cursor)->tokenType == RIGHT_PAREN) {
				return expr;
				//expression complete
			}
			else {
				throw tokens.at(cursor);
			}
		}
		else {
			throw tokens.at(cursor);
		}
	}
	set<string> FIRST(string str) {
		if (str == "scheme") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "schemeList") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "fact") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "factList") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "rule") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "ruleList") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "query") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "queryList") {
			set<string> fset{ "ID" };
			return fset;
		}
		if (str == "headPredicate") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "predicate") {
			set<string> fset{ "ID" };
			return fset;
		}
		else if (str == "predicateList") {
			set<string> fset{ "COMMA" };
			return fset;
		}
		else if (str == "parameterList") {
			set<string> fset{ "COMMA" };
			return fset;
		}
		else if (str == "stringList") {
			set<string> fset{ "COMMA" };
			return fset;
		}
		else if (str == "idList") {
			set<string> fset{ "COMMA" };
			return fset;
		}
		else if (str == "paramter") {
			set<string> fset{ "STRING", "ID", "LEFT_PAREN" };
			return fset;
		}
		else if (str == "expression") {
			set<string> fset{ "LEFT_PAREN" };
			return fset;
		}
		else if (str == "operator") {
			set<string> fset{ "ADD", "MULTIPLY" };
			return fset;
		}
	}
	vector<Predicate*> getSchemeVec() {
		return schemeVec;
	}
	vector<Predicate*> getFactVec() {
		return factVec;
	}
	vector<Rule> getRuleVec() {
		return ruleVec;
	}
	vector<Predicate*> getQueryVec() {
		return queryVec;
	}
	string toString() {
		stringstream output;

		output << "Schemes(";
		output << schemeVec.size();
		output << "):\n";
		for (unsigned int i = 0; i < schemeVec.size(); i++) {
			output << "  " << schemeVec.at(i)->toString() << endl;
		}

		output << "Facts(";
		output << factVec.size();
		output << "):\n";
		for (unsigned int i = 0; i < factVec.size(); i++) {
			output << "  " << factVec.at(i)->toString() << "." << endl;
		}

		output << "Rules(";
		output << ruleVec.size();
		output << "):\n";
		for (unsigned int i = 0; i < ruleVec.size(); i++) {
			output << "  " << ruleVec.at(i).toString() << endl;
		}

		output << "Queries(";
		output << queryVec.size();
		output << "):\n";
		for (unsigned int i = 0; i < queryVec.size(); i++) {
			output << "  " << queryVec.at(i)->toString() << "?" << endl;
		}

		output << "Domain(";
		output << domain.size();
		output << "):\n";
		set<string>::iterator it = domain.begin();
		while (it != domain.end()) {
			output << "  " << (*it) << endl;
			it++;
		}

		return output.str();
	}

private:
	int cursor = 0;
	vector<Token*> tokens;
	vector<Predicate*> schemeVec;
	vector<Predicate*> factVec;
	vector<Rule> ruleVec;
	Predicate Query;
	vector<Predicate*> queryVec;
	set<string> domain;
};

#endif