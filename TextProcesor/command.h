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
	int idx1;
	std::string str;
public:
	InsertCommand(int _idx1, const std::string & _str) : idx1(_idx1), str(_str) {}
	void Execute();
	void unExecute();
};

class DeleteCommand final : public Command {
	int idx1;
	int idx2;
	std::string delstr;
public:
	DeleteCommand(int _idx1, int _idx2) : idx1(_idx1), idx2(_idx2) {}
	void Execute();
	void unExecute();
};

class CopyCommand final : public Command {
	int idx1;
	int idx2;
public:
	CopyCommand(int _idx1, int _idx2) : idx1(_idx1), idx2(_idx2) {}
	void Execute();
	void unExecute() {}
};


class PasteCommand final : public Command {
	int idx1;
public:
	PasteCommand(int _idx) : idx1(_idx) {}
	void Execute();
	void unExecute();
};