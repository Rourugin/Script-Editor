#include "scripteditor.h"


ScriptEditor::ScriptEditor(QWidget *parent) : QMainWindow(parent)
{
    menuBar()->setNativeMenuBar(false);

    SetupUI();
    SetupFormatting();
    CreateActions();
    CreateMenus();
    CheckNestingLevel();
}

ScriptEditor::~ScriptEditor() {}

void ScriptEditor::SetupUI()
{
    pTextEdit = new QTextEdit(this);
    setCentralWidget(pTextEdit);
    setWindowTitle("Script Editor");
    resize(800, 600);
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
    connect(pTextEdit, &QTextEdit::textChanged, this, &ScriptEditor::OnTextChanged);
    connect(pOpenFileAction, &QAction::triggered, this, &ScriptEditor::OpenFile);
    connect(pSaveFileAction, &QAction::triggered, this, &ScriptEditor::SaveFile);
    connect(pNewFileAction, &QAction::triggered, this, &ScriptEditor::NewFile);
}

void ScriptEditor::CreateMenus()
{
    qDebug() << "CreateMenus called";
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

void ScriptEditor::CheckNestingLevel()
{
    if (openTags.isEmpty())
    {
        statusBar()->showMessage("General");
        return;
    }

    QString nestingPath;
    for (int i = 0; i < openTags.size(); ++i)
    {
        if (i > 0) nestingPath += "->";

        QString tag = openTags.at(i);
        QString displayName;

        if (tag == "animation") displayName = "Animation";
        else if (tag == "video") displayName = "Video";
        else if (tag == "image") displayName = "Image";
        else if (tag == "audio") displayName = "Audio";
        else if (tag == "gif") displayName = "GIF";
        else if (tag == "effect") displayName = "Effect";
        else if (tag == "note") displayName = "Note";

        nestingPath += displayName;
    }

    statusBar()->showMessage(nestingPath);
}

void ScriptEditor::NewFile()
{
    //code
}

void ScriptEditor::OpenFile()
{
    //code
}

void ScriptEditor::SaveFile()
{
    //code
}

void ScriptEditor::OnTextChanged()
{
    QTextCursor cursor = pTextEdit->textCursor();
    QString currentText = pTextEdit->toPlainText();
    int cursorPos = cursor.position();

    if (cursorPos > 0 && currentText.length() >= cursorPos)
    {
        QChar lastChar = currentText.at(cursorPos - 1);

        if (lastChar == ']' && !openTags.isEmpty())
        {
            QString lastTag = openTags.pop();
            pTextEdit->setFocus();
        }
    }
    CheckNestingLevel();
}

void ScriptEditor::InsertTextMarker()
{
    //code
}

void ScriptEditor::InsertAnimationMarker()
{
    //code
}

void ScriptEditor::InsertEffectsMarcker()
{
    //code
}

void ScriptEditor::InsertVideoMarker()
{
    //code
}

void ScriptEditor::InsertImageMarker()
{
    //code
}

void ScriptEditor::InsertAudioMarker()
{
    //code
}

void ScriptEditor::InsertNoteMarker()
{
    //code
}

void ScriptEditor::InsertGifMarker()
{
    //code
}
