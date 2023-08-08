#include "JsonConverter.h"

JsonConverter::JsonConverter(IReader& r) : IConverter(r) { } // implementazione costruttore di default


string JsonConverter::fromObject(const AbstractProduct* item) const {
    // logica per convertire un oggetto da AbstractProduct* a string (QJsonObject)
}

AbstractProduct* JsonConverter::toObject(const string& json) const {
    // logica per convertire un oggetto da string (QJsonObject) a AbstractProduct* 
}