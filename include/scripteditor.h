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
    void NewFile();
    void OpenFile();
    void SaveFile();
    void InsertTextMarker(const QString &style = "normal");
    void InsertAnimationMarker(const QString &note ="");
    void InsertEffectsMarcker(const QString &note = "");
    void InsertVideoMarker(const QString &note = "");
    void InsertImageMarker(const QString &note = "");
    void InsertAudioMarker(const QString &note = "");
    void InsertNoteMarker(const QString &note = "");
    void InsertGifMarker(const QString &note = "");

private:
    QToolBar* pMainToolBar;
    QTextEdit* pTextEdit;
    QMenu* pInsertMenu;
    QMenu* pFileMenu;

    QAction* pAnimationMarkerAction;
    QAction* pEffectMarkerAction;
    QAction* pVideoMarkerAction;
    QAction* pAudioMarkerAction;
    QAction* pImageMarkerAction;
    QAction* pTextMarkerAction;
    QAction* pNoteMarkerAction;
    QAction* pGifMarkerAction;
    QAction* pOpenFileAction;
    QAction* pSaveFileAction;
    QAction* pNewFileAction;

    QMap<QString, QTextCharFormat> textFormats;

    void SetupUI();
    void SetupFormatting();
    void CreateActions();
    void CreateMenus();


};

#endif
