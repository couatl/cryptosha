QT += core
QT -= gui

CONFIG += c++11

TARGET = qcryptosha
CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++14



TEMPLATE = app

SOURCES += \
    ../QtCryptosha/settings.cpp \
    ../QtCryptosha/Source.cpp \
    ../QtCryptosha/Interpretator/calc.cpp \
    ../QtCryptosha/Interpretator/interpretator.cpp \
    ../QtCryptosha/Interpretator/analysis/analysis.cpp \
    ../QtCryptosha/Interpretator/analysis/bitset_pool.cpp \
    ../QtCryptosha/xElements/basic_element.cpp \
    ../QtCryptosha/xElements/fabric.cpp \
    ../QtCryptosha/xElements/graphic_scheme.cpp \
    ../QtCryptosha/xElements/xScheme.cpp \
    ../QtCryptosha/Interpretator/cparse/catch.cpp \
    ../QtCryptosha/Interpretator/cparse/functions.cpp \
    ../QtCryptosha/Interpretator/cparse/objects.cpp \
    ../QtCryptosha/Interpretator/cparse/operations.cpp \
    ../QtCryptosha/Interpretator/cparse/packToken.cpp \
    ../QtCryptosha/Interpretator/cparse/shunting-yard.cpp \
    ../QtCryptosha/Interpretator/cparse/test-shunting-yard.cpp \
    ../QtCryptosha/Interpretator/reader/Reader.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    ../QtCryptosha/cryptosha.hpp \
    ../QtCryptosha/easylogging++.h \
    ../QtCryptosha/settings.h \
    ../QtCryptosha/Interpretator/calc.h \
    ../QtCryptosha/Interpretator/interpretator.h \
    ../QtCryptosha/Interpretator/analysis/analysis.h \
    ../QtCryptosha/Interpretator/analysis/bitset_pool.h \
    ../QtCryptosha/xElements/basic_element.h \
    ../QtCryptosha/xElements/binary_element.h \
    ../QtCryptosha/xElements/fabric.h \
    ../QtCryptosha/xElements/graphic_scheme.h \
    ../QtCryptosha/xElements/unary_elements.h \
    ../QtCryptosha/xElements/xScheme.h \
    ../QtCryptosha/Interpretator/cparse/catch.hpp \
    ../QtCryptosha/Interpretator/cparse/functions.h \
    ../QtCryptosha/Interpretator/cparse/objects.h \
    ../QtCryptosha/Interpretator/cparse/pack.h \
    ../QtCryptosha/Interpretator/cparse/packToken.h \
    ../QtCryptosha/Interpretator/cparse/shunting-yard.h \
    ../QtCryptosha/Interpretator/cparse/shunting-yard-exceptions.h \
    ../QtCryptosha/Interpretator/reader/Reader.h

DISTFILES += \
    for.txt
