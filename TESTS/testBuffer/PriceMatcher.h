#ifndef PRICEMATCHER_H
#define PRICEMATCHER_H

#include "IMatcher.h"

class PriceMatcher : public IMatcher {
private:
    const unsigned int lowerBound;
    const unsigned int upperBound;
public:
    PriceMatcher(const unsigned int lowerBound, const unsigned int upperBound);
    virtual bool hasMatch(const AbstractProduct&) const;
};

#endif // PRICEMATCHER_H
