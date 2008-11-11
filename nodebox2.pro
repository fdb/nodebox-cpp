# -------------------------------------------------
# Project created by QtCreator 2008-11-11T20:12:37
# -------------------------------------------------
QT += network \
    opengl \
    script \
    svg \
    webkit \
    xml \
    qtestlib
TARGET = nodebox2
TEMPLATE = app
SOURCES += main.cpp \
    nodeboxdocument.cpp \
    nodeboxapplication.cpp \
    typeshandler.cpp \
    parametertype.cpp \
    parameter.cpp \
    outputparameter.cpp \
    nodetype.cpp \
    nodelibraryversion.cpp \
    nodelibrarymanager.cpp \
    nodelibrary.cpp \
    node.cpp \
    network.cpp \
    connection.cpp
HEADERS += nodeboxdocument.h \
    nodeboxapplication.h \
    typeshandler.h \
    parametertype.h \
    parameter.h \
    outputparameter.h \
    nodetype.h \
    nodelibraryversion.h \
    nodelibrarymanager.h \
    nodelibrary.h \
    node.h \
    network.h \
    connection.h
FORMS += nodeboxdocument.ui
