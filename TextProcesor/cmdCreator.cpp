#include "cmdCreator.h"

/*\
cmd::cmd(std::string inpStr) {
	std::istringstream inp(inpStr);
	std::string w1, w2, w3, w4;
	inp >> w1;

	if (w1 == "insert") {
		code = 'i';
		inp >> this->str;
		str = str.substr(1, str.size() - 2);
		inp >> w3;
		idx1 = std::stoi(w3);
		idx2 = 0;
	}
	else if (w1 == "delete") {
		code = 'd';
		str = "";
		inp >> w2 >> w3;
		idx1 = std::stoi(w2);
		idx2 = std::stoi(w3);
	}
	else if (w1 == "copy") {
		code = 'c';
		inp >> w2 >> w3;
		idx1 = std::stoi(w2);
		idx2 = std::stoi(w3);
	}
	else if (w1 == "paste") {
		code = 'p'; 
		inp >> w2;
		idx1 = std::stoi(w2);
		idx2 = 0;
	}
	else if (w1 == "undo") {
		code = 'u';
		idx1 = 0;
		idx2 = 0;
	}
	else if (w1 == "redo") {
		code = 'r';
		idx1 = 0;
		idx2 = 0;
	}
	else {
		UnknownCommandException();
	}
}
*/

Command * cmdCreator::createCommand(std::istream& inpStream, const std::string& cmdName)
{
	
	std::string word1, word2, word3, word4;
	//inpStream >> word1;

	if (cmdName == "insert") {
		inpStream >> word1 >> word2;
		word1 = word1.substr(1, word1.size() - 2);
		return new InsertCommand(std::stoi(word2), word1);
	}
	else if (cmdName == "delete") { 
		inpStream >> word1 >> word2;
		return new DeleteCommand(std::stoi(word1), std::stod(word2));
	}
	else if (cmdName == "copy") {
		inpStream >> word1 >> word2;
		return new CopyCommand(std::stoi(word1), std::stod(word2));
	}
	else if (cmdName == "paste") {
		inpStream >> word1;
		return new PasteCommand(std::stod(word1));
	} else {
		UnknownCommandException();
	}
	return nullptr;
}
