#include "Buffer.h"


Buffer::Buffer() {}; // comportamento costruttore standard.

// controlla se un elemento esiste all'interno del buffer
bool Buffer::exists(const unsigned int key) const {
	it = memoryBuffer.find(key);
	return (it != memoryBuffer.end());
}


Buffer& Buffer::insert(const unsigned int key, AbstractProduct* product) {
	memoryBuffer[key] = product;
	return *this;
}


Buffer& Buffer::remove(const unsigned int key) {
	memoryBuffer.erase(key);	
	return *this;
}

AbstractProduct* Buffer::get(const unsigned int key) const {
	return memoryBuffer[key];
}

Buffer& Buffer::modify(const unsigned int key, AbstractProduct* product) {
	memoryBuffer[key] = product;
	return *this;
}

const std::map<unsigned int, AbstractProduct*>& Buffer::getMemoryBuffer() const {
	return memoryBuffer;
}

std::vector<AbstractProduct*> readAll() const {
	std::vector	aux;
	
	for(auto it = memoryBuffer.begin(); it != memoryBuffer.end(); it++) {
		aux.push_back(*it);
	}

	return aux;
}

void Buffer::clear() {
	memroyBuffer.erase(memoryBuffer.begin(), memoryBuffer.end());
}
