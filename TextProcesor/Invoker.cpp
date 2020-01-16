#include "Invoker.h"
#include <iostream>

Invoker::Invoker(Document* _doc)
{
	doc = _doc;
}

Invoker::Invoker(std::unique_ptr<Document>& _doc) {
	doc = _doc.get();
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
	DeletedCommand.emplace_back(DoneCommands.back().release());
	DoneCommands.pop_back();

}

void Invoker::Redo() {
	if (DeletedCommand.size() == 0) return;
	DeletedCommand.back()->Execute();
	DoneCommands.emplace_back(DeletedCommand.back().release());
	DeletedCommand.pop_back();
}

void Invoker::Show(std::ostream& outputStream) {
	outputStream << doc->data() << std::endl;
}