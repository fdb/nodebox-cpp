TEMPLATE = app
TARGET = test_nodecore
SOURCES += testnodecore.cpp
QT += testlib
INCLUDEPATH += ../../src/nodecore/node
LIBS += -L../../build -lnodecore
DESTDIR = ../../../build
