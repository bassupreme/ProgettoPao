#include "PriceMatcher.h"



PriceMatcher::PriceMatcher(const unsigned int lowerBound, const unsigned int upperBound) : lowerBound(lowerBound), upperBound(upperBound) { }

bool PriceMatcher::hasMatch(const AbstractProduct& product) const {
    return (product.getPrezzo() > lowerBound && product.getPrezzo() < upperBound);
}
