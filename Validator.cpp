#include "Validator.h"

Validator::Validator() {
	
	reg.assign("[a-zA-Z0-9]{1,20}");
}

bool Validator::check() {

	return std::regex_match(variables, reg);
}
