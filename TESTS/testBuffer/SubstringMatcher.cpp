#include "SubstringMatcher.h"


bool SubstringMatcher::matches(const AbstractProduct & product) const {
    const std::string& stringa = product.getNome();
    int x = stringa.find(substring, 0);

    if (x == -1) return false;
    return true;
}

SubstringMatcher::SubstringMatcher(const std::string& substring) : substring(substring) {}

bool SubstringMatcher::hasMatch(const AbstractProduct& product) const {
    return matches(product);
}
