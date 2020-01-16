#pragma once

#include <vector>
#include "command.h"
#include "document.h"
#include "cmdCreator.h"

class Invoker {
	std::vector<std::shared_ptr<Command>> DoneCommands;
	std::vector<std::shared_ptr<Command>> DeletedCommand;
	std::shared_ptr<Document> doc;
	//Document* doc;
	std::shared_ptr<Command> command;
public:
	Invoker(Document* _doc);
	Invoker(std::shared_ptr<Document> _doc);
	void Do(const std::string& cmdName, std::istream& inpStream);
	void Undo();
	void Redo();
	void Show(std::ostream& outputStream);
};