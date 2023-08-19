#ifndef FILTER_H
#define FILTER_H

// direttive d'inclusione
#include <vector>
#include "IMatcher.h"

class Filter {
private:
    std::vector<const IMatcher*> matchers;
public:
    ~Filter();
    Filter& addMatcher(const IMatcher*);
    bool matchesAll(const AbstractProduct&) const;
};

#endif // FILTER_H
