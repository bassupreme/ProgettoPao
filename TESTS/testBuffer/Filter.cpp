#include "Filter.h"


Filter::~Filter() {
    std::vector<const IMatcher*>::const_iterator it = matchers.begin();
    for (; it != matchers.end(); it++) {
        delete *it;
    }
}

Filter& Filter::addMatcher(const IMatcher* matcher) {
    matchers.push_back(matcher);
    return *this;
}

bool Filter::matchesAll(const AbstractProduct& product) const {
    std::vector<const IMatcher*>::const_iterator it = matchers.begin();
    for (; it != matchers.end(); it++) {
        if (!(*it)->hasMatch(product)) return false;
    }
    return true; // in caso passa tutti i controlli
}


