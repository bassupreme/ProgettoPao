#ifndef SUBSTRINGMATCHER_H
#define SUBSTRINGMATCHER_H

#include <string>
#include "IMatcher.h"
#include "AbstractProduct.h"

class SubstringMatcher : public IMatcher {
private:
    const std::string substring;
    bool matches(const AbstractProduct&) const;
public:
    SubstringMatcher(const std::string&);
    virtual bool hasMatch(const AbstractProduct&) const;
};

#endif // SUBSTRINGMATCHER_H
