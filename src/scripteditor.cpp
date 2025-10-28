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
