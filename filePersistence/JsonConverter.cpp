#include "JsonConverter.h"

JsonConverter::JsonConverter(IReader& r) : IConverter(r) { } // implementazione costruttore di default


string JsonConverter::fromObject(const AbstractProduct* item) {
    // logica per convertire un oggetto da AbstractProduct* a string (QJsonObject)
}

AbstractProduct* JsonConverter::toObject(const string& json) {
    // logica per convertire un oggetto da string (QJsonObject) a AbstractProduct*

}