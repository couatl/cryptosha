#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T17:16:26
#
#-------------------------------------------------

QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cryptosha_graphics
TEMPLATE = app

QMAKE_LFLAGS += -static -static-libgcc

SOURCES += \
    ../Gui/add_dialog.cpp \
    ../Gui/graph_element.cpp \
    ../Gui/graph_layer.cpp \
    ../Gui/graph_pin.cpp \
    ../Gui/graph_scene.cpp \
    ../Gui/graphlayer.cpp \
    ../Gui/graphscheme.cpp \
    ../Gui/lay.cpp \
    ../Gui/main.cpp \
    ../Gui/mainwindow.cpp \
    ../QtCryptosha/settings.cpp \
    ../QtCryptosha/Source.cpp \
    ../QtCryptosha/xElements/basic_element.cpp \
    ../QtCryptosha/xElements/fabric.cpp \
    ../QtCryptosha/xElements/graphic_scheme.cpp \
    ../QtCryptosha/xElements/xScheme.cpp \
    ../QtCryptosha/Interpretator/calc.cpp \
    ../QtCryptosha/Interpretator/interpretator.cpp \
    ../QtCryptosha/Interpretator/analysis/analysis.cpp \
    ../QtCryptosha/Interpretator/analysis/bitset_pool.cpp \
    ../QtCryptosha/Interpretator/cparse/catch.cpp \
    ../QtCryptosha/Interpretator/cparse/functions.cpp \
    ../QtCryptosha/Interpretator/cparse/objects.cpp \
    ../QtCryptosha/Interpretator/cparse/operations.cpp \
    ../QtCryptosha/Interpretator/cparse/packToken.cpp \
    ../QtCryptosha/Interpretator/cparse/shunting-yard.cpp \
    ../QtCryptosha/Interpretator/cparse/test-shunting-yard.cpp \
    ../QtCryptosha/Interpretator/reader/Reader.cpp

HEADERS  += \
    ../Gui/add_dialog.h \
    ../Gui/graph_element.h \
    ../Gui/graph_layer.h \
    ../Gui/graph_pin.h \
    ../Gui/graph_scene.h \
    ../Gui/graphlayer.h \
    ../Gui/graphscheme.h \
    ../Gui/lay.h \
    ../Gui/mainwindow.h \
    ../QtCryptosha/cryptosha.hpp \
    ../QtCryptosha/easylogging++.h \
    ../QtCryptosha/settings.h \
    ../QtCryptosha/xElements/basic_element.h \
    ../QtCryptosha/xElements/binary_element.h \
    ../QtCryptosha/xElements/fabric.h \
    ../QtCryptosha/xElements/graphic_scheme.h \
    ../QtCryptosha/xElements/unary_elements.h \
    ../QtCryptosha/xElements/xScheme.h \
    ../QtCryptosha/Interpretator/calc.h \
    ../QtCryptosha/Interpretator/interpretator.h \
    ../QtCryptosha/Interpretator/analysis/analysis.h \
    ../QtCryptosha/Interpretator/analysis/bitset_pool.h \
    ../QtCryptosha/Interpretator/cparse/catch.hpp \
    ../QtCryptosha/Interpretator/cparse/functions.h \
    ../QtCryptosha/Interpretator/cparse/objects.h \
    ../QtCryptosha/Interpretator/cparse/pack.h \
    ../QtCryptosha/Interpretator/cparse/packToken.h \
    ../QtCryptosha/Interpretator/cparse/shunting-yard.h \
    ../QtCryptosha/Interpretator/cparse/shunting-yard-exceptions.h \
    ../QtCryptosha/Interpretator/reader/Reader.h

FORMS    += \
    ../Gui/add_dialog.ui \
    ../Gui/mainwindow.ui

QMAKE_CXXFLAGS += -std = c++14;

DISTFILES += \
    ../QtCryptosha/Interpretator/cparse/LICENSE.mit \
    ../QtCryptosha/Interpretator/cparse/Makefile \
    ../QtCryptosha/Interpretator/reader/Text.txt