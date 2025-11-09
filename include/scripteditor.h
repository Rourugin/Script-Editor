#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QTextEdit>
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QStack>
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
    void SaveAsFile();
    void OnTextChanged();
    void InsertTextMarker();
    void InsertAnimationMarker();
    void InsertEffectsMarcker();
    void InsertVideoMarker();
    void InsertImageMarker();
    void InsertAudioMarker();
    void InsertNoteMarker();
    void InsertGifMarker();

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
    QAction* pSaveAsFileAction;
    QAction* pGifMarkerAction;
    QAction* pOpenFileAction;
    QAction* pSaveFileAction;
    QAction* pNewFileAction;

    QMap<QString, QTextCharFormat> textFormats;
    QStack<QString> openTags;
    QString currentFilePath;

    void SetupUI();
    void SetupFormatting();
    void CreateActions();
    void CreateMenus();
    void CheckNestingLevel();
    bool SaveToFile(const QString& filePath);
    bool LoadFromFile(const QString& filePath);
    bool AskSave();

};

#endif
