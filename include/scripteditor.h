#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QMenu>


class ScriptEditor : public QMainWindow
{
    Q_OBJECT

public:
    ScriptEditor(QWidget *parent = nullptr);
    ~ScriptEditor();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void insertTextMarker(const QString &style = "normal");
    void insertVideoMarker(const QString &description = "");
    void insertAudioMarker(const QString &note = "");

private:
    QTextEdit* pTextEdit;
    QToolBar* pMainToolBar;
    QMenu* pFileMenu;
    QMenu* pInsertMenu;

    QAction* pNewFileAction;
    QAction* pOpenFileAction;
    QAction* pSaveFileAction;
    QAction* pTextMarkerAction;
    QAction* pVideoMarkerAction;
    QAction* pAudioMarkerAction;

    QMap<QString, QTextCharFormat> textFormats;

    void SetupUI();
    void SetupFormatting();
    void CreateActions();
    void CreateMenus();


};

#endif
