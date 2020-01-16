#include "command.h"

void Command::setDocument(std::shared_ptr<Document> _doc) {
	doc.reset(_doc.get());
	docData.reset(&doc->data());
	docBuffer.reset(&doc->buffer());
}

void InsertCommand::Execute() {
	if (idx1 <= docData->size())
		docData->insert(idx1, str);
	else
		docData->insert(docData->size(), str);
}

void InsertCommand::unExecute() {
	docData->erase(idx1, str.size());
}

void isCorrectIndex(int& idx1, int& idx2, size_t size) {
	if (idx1 < 0) idx1 = 0;
	if (idx1 > idx2) {
		int c = idx2;
		idx2 = idx1;
		idx1 = c;
	}
	if (idx1 > size) idx1 = size;
	if (idx2 > size) idx2 = size;
}

void DeleteCommand::Execute() {
	isCorrectIndex(idx1, idx2, docData->size());
	delstr = docData->substr(idx1, idx2 - idx1 + 1);
	docData->erase(idx1, idx2 - idx1 + 1);
}

void DeleteCommand::unExecute() {
	docData->insert(idx1, delstr);
}

void CopyCommand::Execute() {
	std::string& _docBuffer = doc->buffer();
	isCorrectIndex(idx1, idx2, docData->size());
	_docBuffer = docData->substr(idx1, idx2 - idx1 + 1);
}

void PasteCommand::Execute() {
	if (idx1 < 0) idx1 = 0;
	if (idx1 > docData->size()) idx1 = docData->size();
	docData->insert(idx1, *docBuffer);
}

void PasteCommand::unExecute() {
	docData->erase(idx1, idx1 + docBuffer->size());
}
