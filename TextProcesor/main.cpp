#include <iostream>
#include <fstream>

#include "command.h"
#include "document.h"
#include "Invoker.h"
#include "cmdCreator.h"
#include <exception>

class FReadException : public std::exception {
public:
	FReadException() : std::exception("no file") {}
};

int main() {
	std::fstream inpFile("commands.txt");

	if (!inpFile) {
		std::cout << "no file" << std::endl;
		system("pause");
		return 1;
		//throw FReadException();
	}

	std::shared_ptr<Document> doc(new Document);

	Invoker inv(doc);

	std::string cmdName;
	
	while (inpFile >> cmdName) {
		if (cmdName == "undo") inv.Undo(); 
		else if (cmdName == "redo") inv.Redo();
		else inv.Do(cmdName, inpFile);
	}
	inv.Show(std::cout);
	system("pause");
}