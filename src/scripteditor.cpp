#include "scripteditor.h"
#include <QDebug>


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
    setWindowTitle("Script Editor[*]");
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
    
    //text
    QTextCharFormat TextFormat;
    TextFormat.setBackground(QColor(QColorConstants::Svg::grey));
    textFormats["text"] = TextFormat;

    //general
    QTextCharFormat GeneralFormat;
    GeneralFormat.setBackground(QColor());
    textFormats["general"] = GeneralFormat;
    openTags.push("general");
}

void ScriptEditor::CreateActions()
{
    pAnimationMarkerAction = new QAction("&animation", this);
    pEffectMarkerAction = new QAction("&effect", this);
    pSaveAsFileAction = new QAction("&Save As", this);
    pVideoMarkerAction = new QAction("&video", this);
    pAudioMarkerAction = new QAction("&audio", this);
    pImageMarkerAction = new QAction("&image", this);
    pSaveAsFileAction = new QAction("&saveAs", this);
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
    pGifMarkerAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_W));
    pSaveFileAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    pSaveAsFileAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    pOpenFileAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
    pNewFileAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));

    connect(pAnimationMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertAnimationMarker);
    connect(pEffectMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertEffectsMarcker);
    connect(pVideoMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertVideoMarker);
    connect(pAudioMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertAudioMarker);
    connect(pImageMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertImageMarker);
    connect(pTextMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertTextMarker);
    connect(pNoteMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertNoteMarker);
    connect(pTextEdit, &QTextEdit::textChanged, this, [this](){setWindowModified(true);});
    connect(pGifMarkerAction, &QAction::triggered, this, &ScriptEditor::InsertGifMarker);
    connect(pSaveAsFileAction, &QAction::triggered, this, &ScriptEditor::SaveAsFile);
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
    pFileMenu->addAction(pSaveAsFileAction);

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
        else if (tag == "text") displayName = "Text";
        else if (tag == "general") displayName = "General";

        nestingPath += displayName;
    }

    statusBar()->showMessage(nestingPath);
}

void ScriptEditor::NewFile()
{
    if (AskSave() == true)
    {
        pTextEdit->clear();
        currentFilePath.clear();
        setWindowTitle("Script Editro - New File");
        setWindowModified(false);
    }
}

void ScriptEditor::OpenFile()
{
    if (AskSave() == true)
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Script");
        if (fileName.isEmpty() == false)
        {
            LoadFromFile(fileName);
        }
    }
}

bool ScriptEditor::SaveToFile(const QString& filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly) == false)
    {
        QMessageBox::warning(this, "Error", "Cannot save file: " + file.errorString());
        return false;
    }

    file.write(pTextEdit->toPlainText().toUtf8());
    file.close();
    currentFilePath = filePath;
    setWindowModified(false);
    setWindowTitle("Script Editor - " + QFileInfo(filePath).fileName());

    return true;
}

void ScriptEditor::SaveFile()
{
    if (currentFilePath.isEmpty() == true)
    {
        SaveAsFile();
    }
    else if (currentFilePath.isEmpty() == false)
    {
        SaveToFile(currentFilePath);
    }
}

void ScriptEditor::SaveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty() == false)
    {
        SaveToFile(fileName);
    }
}

bool ScriptEditor::AskSave()
{
    if (isWindowModified() == false)
    {
        return true;
    }

    QMessageBox::StandardButton answer = QMessageBox::question(this, "Script Editor",
                                                               "The document has been modified.\nDo you want to save changes?",
                                                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (answer == QMessageBox::Save)
    {
        SaveFile();
        return true;
    }
    if (answer == QMessageBox::Cancel)
    {
        return false;
    }
    return true; //Discard
}

bool ScriptEditor::LoadFromFile(const QString& filePath)
{
    QFile file(filePath);

    if(file.open(QIODevice::ReadOnly) == true)
    {
        pTextEdit->setPlainText(file.readAll());
        currentFilePath = filePath;
        setWindowTitle("Script Editor - " + QFileInfo(filePath).fileName());
        setWindowModified(false);
        return true;
    }

    return false;
}

void ScriptEditor::OnTextChanged()
{
    setWindowModified(true);
}

void ScriptEditor::InsertTextMarker()
{
    QString tag = "text";
    QTextCursor cursor = pTextEdit->textCursor();

    cursor.insertText("[" + tag.toUpper() + ": ", textFormats[tag]);
    pTextEdit->setCurrentCharFormat(textFormats[tag]);
    openTags.push(tag);
    CheckNestingLevel();
}

void ScriptEditor::InsertAnimationMarker()
{
    QString tag = "animation";
    QTextCursor cursor = pTextEdit->textCursor();

    cursor.insertText("[" + tag.toUpper() + ": ", textFormats[tag]);
    pTextEdit->setCurrentCharFormat(textFormats[tag]);
    openTags.push(tag);
    CheckNestingLevel();
}

void ScriptEditor::InsertEffectsMarcker()
{
    QString tag = "effect";
    QTextCursor cursor = pTextEdit->textCursor();

    cursor.insertText("[" + tag.toUpper() + ": ", textFormats[tag]);
    pTextEdit->setCurrentCharFormat(textFormats[tag]);
    openTags.push(tag);
    CheckNestingLevel();
}

void ScriptEditor::InsertVideoMarker()
{
    QString tag = "video";
    QTextCursor cursor = pTextEdit->textCursor();

    cursor.insertText("[" + tag.toUpper() + ": ", textFormats[tag]);
    pTextEdit->setCurrentCharFormat(textFormats[tag]);
    openTags.push(tag);
    CheckNestingLevel();
}

void ScriptEditor::InsertImageMarker()
{
    QString tag = "image";
    QTextCursor cursor = pTextEdit->textCursor();

    cursor.insertText("[" + tag.toUpper() + ": ", textFormats[tag]);
    pTextEdit->setCurrentCharFormat(textFormats[tag]);
    openTags.push(tag);
    CheckNestingLevel();
}

void ScriptEditor::InsertAudioMarker()
{
    QString tag = "audio";
    QTextCursor cursor = pTextEdit->textCursor();

    cursor.insertText("[" + tag.toUpper() + ": ", textFormats[tag]);
    pTextEdit->setCurrentCharFormat(textFormats[tag]);
    openTags.push(tag);
    CheckNestingLevel();
}

void ScriptEditor::InsertNoteMarker()
{
    QString tag = "note";
    QTextCursor cursor = pTextEdit->textCursor();

    cursor.insertText("[" + tag.toUpper() + ": ", textFormats[tag]);
    pTextEdit->setCurrentCharFormat(textFormats[tag]);
    openTags.push(tag);
    CheckNestingLevel();
}

void ScriptEditor::InsertGifMarker()
{
    QString tag = "gif";
    QTextCursor cursor = pTextEdit->textCursor();

    cursor.insertText("[" + tag.toUpper() + ": ", textFormats[tag]);
    pTextEdit->setCurrentCharFormat(textFormats[tag]);
    openTags.push(tag);
    CheckNestingLevel();
}
