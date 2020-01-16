#pragma once
#include <string>
#include <memory>
#include "document.h"

class Command {
protected:
	Document* doc;
	std::string* docData;
	std::string* docBuffer;
public:
	virtual ~Command() {}
	virtual void Execute() = 0;
	virtual void unExecute() = 0;
	void setDocument(Document* _doc);
};

class InsertCommand final : public Command {
	size_t idx;
	std::string str;
public:
	InsertCommand(size_t _idx1, const std::string & _str) : idx(_idx1), str(_str) {}
	void Execute();
	void unExecute();
};

class DeleteCommand final : public Command {
	size_t leftIdx;
	size_t rightIdx;
	std::string deletedStr;
public:
	DeleteCommand(size_t _idx1, size_t _idx2) : leftIdx(_idx1), rightIdx(_idx2) {}
	void Execute();
	void unExecute();
};

class CopyCommand final : public Command {
	size_t leftIdx;
	size_t rightIdx;
public:
	CopyCommand(size_t _idx1, size_t _idx2) : leftIdx(_idx1), rightIdx(_idx2) {}
	void Execute();
	void unExecute() {}
};


class PasteCommand final : public Command {
	size_t idx;
public:
	PasteCommand(size_t _idx) : idx(_idx) {}
	void Execute();
	void unExecute();
};