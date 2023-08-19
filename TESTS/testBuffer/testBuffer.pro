QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AbstractProduct.cpp \
        Buffer.cpp \
        Filter.cpp \
        Fisico.cpp \
        Memory.cpp \
        Noleggio.cpp \
        PriceMatcher.cpp \
        SubstringMatcher.cpp \
        Virtuale.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AbstractProduct.h \
    Buffer.h \
    Container.h \
    Filter.h \
    Fisico.h \
    IConstVisitor.h \
    IMatcher.h \
    IVisitor.h \
    Memory.h \
    Noleggio.h \
    PriceMatcher.h \
    SubstringMatcher.h \
    Virtuale.h
