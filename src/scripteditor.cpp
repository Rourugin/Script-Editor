#include "scripteditor.h"
#include <QApplication>
#include <QMenuBar>


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
    //animation
    QTextCharFormat AnimationFormat;
    AnimationFormat.setBackground(QColor(183, 90, 90));
    textFormats["animation"] = AnimationFormat;

    //video
    QTextCharFormat VideoFormat;
    VideoFormat.setBackground(QColor(103, 185, 184));
    VideoFormat.setFontWeight(QFont::Bold);
    textFormats["video"] = VideoFormat;

    //image
    QTextCharFormat ImageFormat;
    ImageFormat.setBackground(QColor(194, 192, 65));
    textFormats["image"] = ImageFormat;

    //audio
    QTextCharFormat AudioFormat;
    AudioFormat.setBackground(QColor(149, 89, 170));
    textFormats["audio"] = AudioFormat;

    //GIF
    QTextCharFormat GifFromat;
    GifFromat.setBackground(QColor(107, 170, 89));
    textFormats["gif"] = GifFromat;

    //Effect
    QTextCharFormat EffectFormat;
    EffectFormat.setBackground(QColor(76, 80, 206));
    EffectFormat.setFontUnderline(true);
    textFormats["effect"] = EffectFormat;

    //note
    QTextCharFormat NoteFormat;
    NoteFormat.setBackground(QColor(128, 128, 128));
    NoteFormat.setFontItalic(true);
    textFormats["note"] = NoteFormat;
}

void ScriptEditor::CreateActions()
{
    pAnimationMarkerAction = new QAction("&animation", this);
    pEffectMarkerAction = new QAction("&effect", this);
    pVideoMarkerAction = new QAction("&video", this);
    pAudioMarkerAction = new QAction("&audio", this);
    pImageMarkerAction = new QAction("&image", this);
    pTextMarkerAction = new QAction("&Text", this);
    pNoteMarkerAction = new QAction("&note", this);
    pGifMarkerAction = new QAction("&gif", this);
    pOpenFileAction = new QAction("&Open", this);
    pSaveFileAction = new QAction("&Save", this);
    pNewFileAction = new QAction("&New", this);

    pAnimationMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_D));
    pEffectMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_F));
    pVideoMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_V));
    pAudioMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_A));
    pImageMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Z));
    pTextMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_C));
    pNoteMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_X));
    pGifMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    pOpenFileAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
    pSaveFileAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    pNewFileAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));

    connect(pAnimationMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertAnimationMarker);
    connect(pEffectMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertEffectsMarcker);
    connect(pVideoMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertVideoMarker);
    connect(pAudioMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertAudioMarker);
    connect(pImageMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertImageMarker);
    connect(pTextMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertTextMarker);
    connect(pNoteMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertNoteMarker);
    connect(pGifMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertGifMarker);
    connect(pOpenFileAction, &QAction::triggered, this, &ScriptEditor::OpenFile);
    connect(pSaveFileAction, &QAction::triggered, this, &ScriptEditor::SaveFile);
    connect(pNewFileAction, &QAction::triggered, this, &ScriptEditor::NewFile);
}

void ScriptEditor::CreateMenus()
{
    QMenuBar *pMenuBar = this->menuBar();

    pFileMenu = pMenuBar->addMenu("&File");
    pFileMenu->addAction(pNewFileAction);
    pFileMenu->addAction(pOpenFileAction);
    pFileMenu->addAction(pSaveFileAction);

    pInsertMenu = pMenuBar->addMenu(("&Edit"));
    pInsertMenu->addAction(pAnimationMarkerAction);
    pInsertMenu->addAction(pEffectMarkerAction);
    pInsertMenu->addAction(pVideoMarkerAction);
    pInsertMenu->addAction(pImageMarkerAction);
    pInsertMenu->addAction(pAudioMarkerAction);
    pInsertMenu->addAction(pTextMarkerAction);
    pInsertMenu->addAction(pNoteMarkerAction);
    pInsertMenu->addAction(pGifMarkerAction);
}
