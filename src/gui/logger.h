#ifndef Logger_h
#define Logger_h

#include <qtextedit.h>

class Logger : public QTextEdit
{
    Q_OBJECT
public:
    Logger(QWidget *parent = 0);
    virtual ~Logger();

public slots:
    void addError(const QString& msg);
    void addWarning(const QString& msg);
    void addInfo(const QString& msg);
    void addDebug(const QString& msg);
};

#endif // Logger_h
