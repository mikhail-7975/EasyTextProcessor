#pragma once

#include <vector>
#include "command.h"
#include "document.h"
#include "cmdCreator.h"

class Invoker {
	std::vector<std::unique_ptr<Command>> DoneCommands;
	std::vector<std::unique_ptr<Command>> DeletedCommand;
	//std::unique_ptr<Document> doc;
	Document* doc;
	std::unique_ptr<Command> command;
public:
	Invoker(Document* _doc);
	Invoker(std::unique_ptr<Document>& _doc);
	void Do(const std::string& cmdName, std::istream& inpStream);
	void Undo();
	void Redo();
	void Show(std::ostream& outputStream);
};