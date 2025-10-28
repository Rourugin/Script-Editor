#include <QApplication>
#include "scripteditor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ScriptEditor editor;
    editor.show();

    return app.exec();
}
