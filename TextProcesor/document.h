#pragma once
#include <string>

class Document {
	std::string _data;
	std::string _buffer;
public:
	std::string& data();
	std::string& buffer();
	
};