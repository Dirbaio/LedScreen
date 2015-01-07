TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Screen.cpp \
    Preview.cpp

HEADERS += \
    Screen.hpp \
    Preview.hpp

LIBS += -lsfml-graphics -lsfml-system -lsfml-window
