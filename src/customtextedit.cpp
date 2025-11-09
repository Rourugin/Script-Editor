#include "customtextedit.h"


CustomTextEdit::CustomTextEdit(QWidget *parent) : QTextEdit(parent) {}

void CustomTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_BracketRight && event->text() == "]")
    {
        emit CloseTagRequested();
        return;
    }

    QTextEdit::keyPressEvent(event);
}
