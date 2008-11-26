QT = core \
    gui \
    xml \
    webkit \
    svg
DESTDIR = ../../build
TARGET = NodeBox
TEMPLATE = app
SOURCES += main.cpp \
    nodeboxdocument.cpp \
    nodeboxapplication.cpp \
    canvasviewer.cpp \
    codeeditor.cpp \
    logger.cpp
HEADERS += nodeboxdocument.h \
    nodeboxapplication.h \
    canvasviewer.h \
    codeeditor.h \
    logger.h
INCLUDEPATH += ../nodecore/node \
    ../nodecore/graphics \
    ../3rdparty/pythonqt/src \
    /System/Library/Frameworks/Python.framework/Headers
include(../3rdparty/pythonqt/src/pythonqt.pri)
LIBS += -L../../build \
    -lnodecore \
    -framework \
    Python
