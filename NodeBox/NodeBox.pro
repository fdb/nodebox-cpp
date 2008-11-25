# -------------------------------------------------
# Project created by QtCreator 2008-11-11T19:53:15
# -------------------------------------------------
QT += network \
    opengl \
    script \
    svg \
    webkit \
    xml
TARGET = NodeBox
TEMPLATE = app
SOURCES += main.cpp \
    NodeBoxDocument.cpp
HEADERS += NodeBoxDocument.h
FORMS += NodeBoxDocument.ui
SUBDIRS += \
        ../NodeCore
