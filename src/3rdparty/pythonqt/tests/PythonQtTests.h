#ifndef _PYTHONQTTESTS_H
#define _PYTHONQTTESTS_H

/*
 *
 *  Copyright (C) 2006 MeVis Research GmbH All Rights Reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: MeVis Research GmbH, Universitaetsallee 29,
 *  28359 Bremen, Germany or:
 *
 *  http://www.mevis.de
 *
 */

//----------------------------------------------------------------------------------
/*!
// \file    PythonQtTests.h
// \author  Florian Link
// \author  Last changed by $Author: florian $
// \date    2006-05
*/
//----------------------------------------------------------------------------------

#include "PythonQt.h"
#include <QtTest/QtTest>
#include <QVariant>
#include "PythonQtImportFileInterface.h"
#include "PythonQtCppWrapperFactory.h"

class PythonQtTestSlotCallingHelper;
class PythonQtTestApiHelper;
class QWidget;

//! test the PythonQt api
class PythonQtTestApi : public QObject
{
  Q_OBJECT

private slots:
  void initTestCase();
  void testCall();
  void testVariables();
  void testRedirect();
  void testImporter();

private:
  PythonQtTestApiHelper* _helper;

};

//! test the PythonQt api (helper)
class PythonQtTestApiHelper : public QObject , public PythonQtImportFileInterface
{
  Q_OBJECT
public:
  PythonQtTestApiHelper() {
  };

  bool call(const QString& function, const QVariantList& args, const QVariant& expectedResult);

  virtual QByteArray readFileAsBytes(const QString& filename);

  virtual QByteArray readSourceFile(const QString& filename, bool& ok);

  virtual bool exists(const QString& filename);

  virtual QDateTime lastModifiedDate(const QString& filename);

public slots:

  //! call to set that the test has passed (from Python!)
  void setPassed() { _passed = true; }

  void stdOut(const QString&);
  void stdErr(const QString&);

private:
  bool _passed;
};

// test implementation of the wrapper factory
class PythonQtTestCppFactory : public PythonQtCppWrapperFactory 
{
public:
  virtual QObject* create(const QByteArray& name, void *ptr);
};

//! an cpp object to be wrapped
class PQCppObject {

public:
  PQCppObject(int h) { _height = h; }

  int getHeight() { return _height; }
  void setHeight(int h) { _height = h; }

private:
  int _height;
};

//! an qobject that wraps the existing cpp object
class PQCppObjectWrapper : public QObject {
  Q_OBJECT
public:
  PQCppObjectWrapper(void* ptr) {
    _ptr = (PQCppObject*)ptr;
  }

public slots:
  int  getHeight() { return _ptr->getHeight(); }
  void setHeight(int h) { _ptr->setHeight(h); }

private:
  PQCppObject* _ptr;
};

class PQCppObjectDecorator : public QObject {
  Q_OBJECT
public slots:
  int  getH(PQCppObject* obj) { return obj->getHeight(); }

};

//! an cpp object to be wrapped by decorators only
class PQCppObjectNoWrap {

public:
  PQCppObjectNoWrap(int h) { _height = h; }

  int getHeight() { return _height; }
  void setHeight(int h) { _height = h; }

private:
  int _height;
};

class PQCppObjectNoWrapDecorator : public QObject {
  Q_OBJECT
public slots:
  int  getH(PQCppObjectNoWrap* obj) { return obj->getHeight(); }

};


//! test the calling of slots
class PythonQtTestSlotCalling : public QObject
{
  Q_OBJECT

private slots:
  void initTestCase();
  void init();

  void testNoArgSlotCall();
  void testPODSlotCalls();
  void testQVariantSlotCalls();
  void testObjectSlotCalls();
  void testMultiArgsSlotCall();

  void testOverloadedCall();

  void testCppFactory();

private:
  PythonQtTestSlotCallingHelper* _helper;

};

//! helper class for slot calling test
class PythonQtTestSlotCallingHelper : public QObject
{
  Q_OBJECT
public:
  PythonQtTestSlotCallingHelper(PythonQtTestSlotCalling* test) {
    _test = test;
  };

  bool runScript(const char* script, int expectedOverload = -1);

public slots:

  //! call to set that the test has passed (from Python!)
  void setPassed() { _passed = true; }

  //! no arguments, no return value:
  void testNoArg() { _called = true; }

  //! overload test!
  void overload(bool a) { _calledOverload = 0; _called = true; }
  void overload(float a) { _calledOverload = 1; _called = true;}
  void overload(int a) { _calledOverload = 2; _called = true;}
  void overload(const QString& str) { _calledOverload = 3; _called = true;}
  void overload(const QStringList& str) { _calledOverload = 4; _called = true;}
  void overload(QObject* str) { _calledOverload = 5; _called = true;}
  void overload(float a, int b) { _calledOverload = 6; _called = true;}

  //! POD values:
  int getInt(int a) {   _called = true; return a; }
  unsigned int getUInt(unsigned int a) { _called = true;  return a; }
  bool getBool(bool a) { _called = true;  return a; }
  char getChar(char a) { _called = true;  return a; }
  unsigned char getUChar(unsigned char a) { _called = true;  return a; }
  long getLong(long a) { _called = true;  return a; }
  unsigned long getULong(unsigned long a) { _called = true;  return a; }
  short getShort(short a) { _called = true;  return a; }
  unsigned short getUShort(unsigned short a) { _called = true;  return a; }
  QChar getQChar(QChar a) { _called = true;  return a; }
  qint64 getLongLong(qint64 a) { _called = true;  return a; }
  quint64 getULongLong(quint64 a) { _called = true;  return a; }
  double getDouble(double d) { _called = true;  return d; }
  float  getFloat(float d) { _called = true;  return d; }

  //! important qt types:
  QString getQString(const QString& s) { _called = true;  return s; }
  QStringList getQStringList(const QStringList& l) { _called = true;  return l; }
  QVariant getQVariant(const QVariant& var) { _called = true;  return var; }

  //! testing pointer passing
  PythonQtTestSlotCallingHelper* getTestObject(PythonQtTestSlotCallingHelper* obj) {  _called = true; return obj; }
  //! testing inheritance checking
  QObject* getQObject(QObject* obj) { _called = true; return obj; }
  QWidget* getQWidget(QWidget* obj) { _called = true; return obj; }
  //! testing if an object that was not wrapped is wrapped earlier is wrapped correctly
  QObject* getNewObject() { _called = true; return new PythonQtTestSlotCallingHelper(NULL); }

  QVariantList getMultiArgs(int a, double b, const QString& str) { _called = true; return (QVariantList() << a << b << str); }
  // more exotic, not yet tested
  //void setByteArray(QByteArray array) { qDebug() << array.data(); }
  //void setCharPtr(char* data) { qDebug() << data; }

  //! cpp wrapper factory test
  PQCppObject* createPQCppObject(int h) { _called = true; return new PQCppObject(h); }

  //! cpp wrapper factory test
  PQCppObject* getPQCppObject(PQCppObject* p) { _called = true; return p; }

  //! cpp wrapper factory test
  PQCppObjectNoWrap* createPQCppObjectNoWrap(int h) { _called = true; return new PQCppObjectNoWrap(h); }

  //! cpp wrapper factory test
  PQCppObjectNoWrap* getPQCppObjectNoWrap(PQCppObjectNoWrap* p) { _called = true; return p; }

private:
  bool _passed;
  bool _called;
  int  _calledOverload;
  PythonQtTestSlotCalling* _test;
};

class PythonQtTestSignalHandlerHelper;

//! test the connection of signals to python
class PythonQtTestSignalHandler : public QObject
{
  Q_OBJECT

private slots:
  void initTestCase();

  void testSignalHandler();
  void testRecursiveSignalHandler();

private:
  PythonQtTestSignalHandlerHelper* _helper;

};

//! helper class for signal testing
class PythonQtTestSignalHandlerHelper : public QObject
{
  Q_OBJECT

public:
  PythonQtTestSignalHandlerHelper(PythonQtTestSignalHandler* test) {
    _test = test;
  };

public slots:
  void setPassed() { _passed = true; }

  bool emitIntSignal(int a) { _passed = false; emit intSignal(a); return _passed; };
  bool emitFloatSignal(float a) { _passed = false; emit floatSignal(a); return _passed; };

  bool emitVariantSignal(const QVariant& v) { _passed = false; emit variantSignal(v); return _passed; };
  QVariant expectedVariant() { return _v; }
  void setExpectedVariant(const QVariant& v) { _v = v; }

  bool emitComplexSignal(int a, float b, const QStringList& l, QObject* obj) { _passed = false; emit complexSignal(a,b,l,obj); return _passed; };

  bool emitSignal1(int a) { _passed = false; emit signal1(a); return _passed; };
  bool emitSignal2(const QString& s) { _passed = false; emit signal2(s); return _passed; };
  bool emitSignal3(float a) { _passed = false; emit signal3(a); return _passed; };

signals:
  void intSignal(int);
  void floatSignal(float);
  void variantSignal(const QVariant& v);
  void complexSignal(int a, float b, const QStringList& l, QObject* obj);

  void signal1(int);
  void signal2(const QString&);
  void signal3(float);

private:
  bool _passed;
  QVariant _v;

  PythonQtTestSignalHandler* _test;
};

#endif
