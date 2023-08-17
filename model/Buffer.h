#ifndef BUFFER_H
#define BUFFER_H

#include <map>
#include <vector>
#include "AbstractProduct.h"

class Buffer {
private:
	std::map<unsigned int, AbstractProduct*> memoryBuffer;

public:
	Buffer();
	bool exists(const unsigned int) const;
	Buffer& insert(const unsigned int, AbstractProduct*);
	Buffer& remove(const unsigned int);
	AbstractProduct* get(const unsigned int) const;
	Buffer& modify(const unsigned int, AbstractProduct*);
	const std::map<unsigned int, AbstractProduct*>& getMemoryBuffer() const;
	std::vector<AbstractProduct*> readAll() const;
	void clear();
};

#endif
