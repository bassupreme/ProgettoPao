#include "Buffer.h"


// comportamento costruttore standard.
void Buffer::destroy(const std::map<unsigned int, AbstractProduct*>& b) {
    std::map<unsigned int, AbstractProduct*>::const_iterator it;
    for(it = b.begin(); it != b.end(); it++) {
        std::cout << (*it).second << std::endl;
        delete it->second;
    }
}

Buffer::Buffer() {}

Buffer::~Buffer() {
    destroy(memoryBuffer);
}

// controlla se un elemento esiste all'interno del buffer
bool Buffer::exists(const unsigned int key) const {
    std::map<unsigned int, AbstractProduct*>::const_iterator it = memoryBuffer.find(key);
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

const AbstractProduct* Buffer::get(const unsigned int key) const {
    std::map<unsigned int, AbstractProduct*>::const_iterator it = memoryBuffer.find(key);

    if (it == memoryBuffer.end()) {
        throw std::out_of_range("id non esistente");
    }
    return it->second;
}

Buffer& Buffer::modify(const unsigned int key, AbstractProduct* product) {
    memoryBuffer[key] = product;
    return *this;
}

const std::map<unsigned int, AbstractProduct*>& Buffer::getMemoryBuffer() const {
    return memoryBuffer;
}

std::vector<AbstractProduct*> Buffer::readAll() const {
    std::vector<AbstractProduct*> aux;
    for(auto it = memoryBuffer.begin(); it != memoryBuffer.end(); it++) {
        aux.push_back(it->second);
    }

    return aux;
}

void Buffer::clear() {
    destroy(memoryBuffer);
    memoryBuffer.erase(memoryBuffer.begin(), memoryBuffer.end());
}

bool Buffer::empty() const {
    return memoryBuffer.empty();
}
