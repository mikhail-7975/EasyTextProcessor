#include "Invoker.h"
#include <iostream>

Invoker::Invoker(Document* _doc)
{
	doc.reset(_doc);
}

Invoker::Invoker(std::shared_ptr<Document> _doc) {
	doc.reset(_doc.get());
}

void Invoker::Do(const std::string& cmdName, std::istream& inpStream) {
	command = nullptr;
	command.reset(cmdCreator::createCommand(inpStream, cmdName));
	if (command != nullptr) {
		command->setDocument(doc);
		command->Execute();
		if (cmdName != "copy") {
			DoneCommands.resize(DoneCommands.size() + 1);
			DoneCommands.back().swap(command);
		}//
	}
}

void Invoker::Undo() {
	if (DoneCommands.size() == 0) return;
	/*command = */
	DoneCommands.back()->unExecute();
	DeletedCommand.emplace_back(DoneCommands.back().get());
	DoneCommands.pop_back();
	
}

void Invoker::Redo() {
	if (DeletedCommand.size() == 0) return;
	DeletedCommand.back()->Execute();
	DoneCommands.emplace_back(DeletedCommand.back());
	DeletedCommand.pop_back();
}

void Invoker::Show(std::ostream& outputStream) {
	outputStream << doc->data() << std::endl;
}