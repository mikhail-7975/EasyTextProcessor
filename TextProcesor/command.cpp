#include "command.h"
 
void Command::setDocument(Document* _doc) {
	doc = _doc;
	docData = &doc->data();
	docBuffer = &doc->buffer();
}

void InsertCommand::Execute() {
	if (idx <= docData->size())
		docData->insert(idx, str);
	else
		docData->insert(docData->size(), str);
}

void InsertCommand::unExecute() {
	docData->erase(idx, str.size());
}

void setIndexInDocRange(size_t& idx1, size_t& idx2, size_t size) {
	if (idx1 > size) idx1 = size;
	if (idx2 > size) idx2 = size;
}

void DeleteCommand::Execute() {
	setIndexInDocRange(leftIdx, rightIdx, docData->size());
	deletedStr = docData->substr(leftIdx, rightIdx - leftIdx + 1);
	docData->erase(leftIdx, rightIdx - leftIdx + 1);
}

void DeleteCommand::unExecute() {
	docData->insert(leftIdx, deletedStr);
}

void CopyCommand::Execute() {
	std::string& _docBuffer = doc->buffer();
	setIndexInDocRange(leftIdx, rightIdx, docData->size());
	_docBuffer = docData->substr(leftIdx, rightIdx - leftIdx + 1);
}

void PasteCommand::Execute() {
	if (idx < 0) idx = 0;
	if (idx > docData->size()) idx = docData->size();
	docData->insert(idx, *docBuffer);
}

void PasteCommand::unExecute() {
	docData->erase(idx, idx + docBuffer->size());
}
