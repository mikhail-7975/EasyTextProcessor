#pragma once
#include <string>
#include <exception>
#include <sstream>

#include "cmdCreator.h"
#include "command.h"

class cmdCreator final {
public:
	static Command* createCommand(std::istream& inputStream, const std::string& cmdName); 
};


class UnknownCommandException final: public std::exception {
public:
	UnknownCommandException() : std::exception("unknown command") {}
};