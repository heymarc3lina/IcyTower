#pragma once
#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <regex>
#include <string>

class Validator {
	std::regex reg;
	std::string variables;
public:
	//metoda sprawdzajaca poprawnosc wyrazenia
	bool check();
	Validator();
	void inline setVariables(const std::string &newVariables) {
		this->variables = newVariables;
	}
};

#endif