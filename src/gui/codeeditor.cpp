#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent)
          : QTextEdit(parent)
{
    setAcceptRichText(false);
}

CodeEditor::~CodeEditor()
{
}
