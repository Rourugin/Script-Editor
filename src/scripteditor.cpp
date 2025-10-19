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
