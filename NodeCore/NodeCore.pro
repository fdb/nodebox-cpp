# -------------------------------------------------
# Project created by QtCreator 2008-11-04T18:51:31
# -------------------------------------------------
QT -= gui
QT += script xml script
TARGET = NodeCore
TEMPLATE = lib
DEFINES += NODECORE_LIBRARY
SOURCES += node/posixutils.cpp \
    node/Parameter.cpp \
    node/NodeLibraryManager.cpp \
    node/NodeLibrary.cpp \
    node/Node.cpp \
    node/Network.cpp \
    node/Connection.cpp \
    node/NodeType.cpp \
    node/ParameterType.cpp \
    node/NodeLibraryVersion.cpp \
    node/TypesHandler.cpp \
    node/OutputParameter.cpp
HEADERS += NodeCoreGlobal.h \
    node/posixutils.h \
    node/Parameter.h \
    node/NodeLibraryManager.h \
    node/NodeLibrary.h \
    node/Node.h \
    node/Network.h \
    node/Connection.h \
    node/ParameterType.h \
    node/OutputParameter.h \
    node/NodeType.h \
    node/NodeLibraryVersion.h \
    node/TypesHandler.h
