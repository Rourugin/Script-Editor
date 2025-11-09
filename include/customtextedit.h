#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QWidget>

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit CustomTextEdit(QWidget *parent = nullptr);

signals:
    void CloseTagRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif
