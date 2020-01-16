#include "document.h"
#include <iostream>

std::string & Document::data()
{
	return _data;
}

std::string & Document::buffer() {
	return _buffer;
}
