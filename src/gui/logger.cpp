#include "logger.h"

Logger::Logger(QWidget *parent)
      : QTextEdit(parent)
{
    setReadOnly(true);
}

Logger::~Logger()
{
}

void Logger::addError(const QString& msg)
{
    insertHtml("<font color=red>" + msg + "</font><br>");
}

void Logger::addWarning(const QString& msg)
{
    insertHtml("<font color=green>" + msg + "</font><br>");
}

void Logger::addInfo(const QString& msg)
{
    insertHtml(msg + "<br>");
}

void Logger::addDebug(const QString& msg)
{
    insertHtml("<font color=gray>" + msg + "</font><br>");
}
