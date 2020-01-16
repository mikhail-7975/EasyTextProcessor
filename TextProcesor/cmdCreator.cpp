#include "cmdCreator.h"

int makeNotNegativeIndex(int i) {
	if (i < 0)
		i = 0;
	return i;
}

Command* cmdCreator::createCommand(std::istream& inpStream, const std::string& cmdName)
{
	std::string word1, word2, word3, word4;

	if (cmdName == "insert") {
		inpStream >> word1 >> word2;
		word1 = word1.substr(1, word1.size() - 2);
		int idx = makeNotNegativeIndex(std::stoi(word2));
		return new InsertCommand(static_cast<size_t>(idx), word1);
	}
	else if (cmdName == "delete") { 
		inpStream >> word1 >> word2;

		int idx1 = makeNotNegativeIndex(std::stoi(word1));
		int idx2 = makeNotNegativeIndex(std::stoi(word2));
		if (idx1 > idx2)
			std::swap(idx1, idx2);

		return new DeleteCommand(static_cast<size_t>(idx1), static_cast<size_t>(idx2));
	}
	else if (cmdName == "copy") {
		inpStream >> word1 >> word2;
		
		int idx1 = makeNotNegativeIndex(std::stoi(word1));
		int idx2 = makeNotNegativeIndex(std::stoi(word2));
		
		if (idx1 > idx2)
			std::swap(idx1, idx2);

		return new CopyCommand(static_cast<size_t>(idx1), static_cast<size_t>(idx2));
	}
	else if (cmdName == "paste") {
		inpStream >> word1;
		int idx = makeNotNegativeIndex(std::stoi(word1));
		return new PasteCommand(static_cast<size_t>(idx));
	} else {
		throw UnknownCommandException();
	}
	return nullptr;
}
