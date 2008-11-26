#ifndef CodeEditor_h
#define CodeEditor_h

#include <qtextedit.h>

class CodeEditor : public QTextEdit
{
    Q_OBJECT
public:
    CodeEditor(QWidget *parent = 0);
    virtual ~CodeEditor();
};

#endif // CodeEditor_h
