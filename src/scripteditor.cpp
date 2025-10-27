#include "scripteditor.h"
#include <QApplication>


ScriptEditor::ScriptEditor(QWidget *parent) : QMainWindow(parent)
{
    SetupUI();
    SetupFormatting();
    CreateActions();
    CreateMenus();
}

ScriptEditor::~ScriptEditor() {}

void ScriptEditor::SetupUI()
{
    pTextEdit = new QTextEdit(this);
    setCentralWidget(pTextEdit);
    setWindowTitle("Script Editor");
    resize(1920, 1080);
}

void ScriptEditor::SetupFormatting()
{

}
