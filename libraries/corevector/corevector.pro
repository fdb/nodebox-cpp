TEMPLATE = lib
CONFIG += plugin
HEADERS = corevectorfactory.h \
          rectnode.h

SOURCES = corevectorfactory.cpp \
          rectnode.cpp

DESTDIR = ../../build

INCLUDEPATH += ../../src/nodecore/node
LIBS += -L../../build -lnodecore
