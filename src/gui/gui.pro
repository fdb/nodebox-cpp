QT = core \
    gui \
    xml \
    webkit \
    svg
DESTDIR    = ../../build
TARGET = NodeBox
TEMPLATE = app
SOURCES += main.cpp \
    nodeboxdocument.cpp \
    nodeboxapplication.cpp \

HEADERS += \
    nodeboxdocument.h \
    nodeboxapplication.h

INCLUDEPATH += ../nodecore/node
LIBS += -L../../build -lnodecore
