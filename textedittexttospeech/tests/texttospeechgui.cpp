/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechgui.h"
using namespace Qt::Literals::StringLiterals;

#include "texttospeech.h"
#include <KLocalizedString>
#include <QAction>
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QStandardPaths>
#include <QTextEdit>

TextToSpeechGui::TextToSpeechGui(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(u"text to speech window"_s);
    mEdit = new QTextEdit;
    setCentralWidget(mEdit);

    QMenu *editMenu = menuBar()->addMenu(u"Edit"_s);

    auto act = new QAction(i18nc("@action", "Speech text"), this);
    connect(act, &QAction::triggered, this, &TextToSpeechGui::slotTextToSpeech);
    editMenu->addAction(act);
    qDebug() << " isReady ? " << TextEditTextToSpeech::TextToSpeech::self()->isReady();
}

TextToSpeechGui::~TextToSpeechGui() = default;

void TextToSpeechGui::slotTextToSpeech()
{
    QString text;
    if (mEdit->textCursor().hasSelection()) {
        text = mEdit->textCursor().selectedText();
    } else {
        text = mEdit->toPlainText();
    }
    if (!text.isEmpty()) {
        TextEditTextToSpeech::TextToSpeech::self()->say(text);
    }
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new TextToSpeechGui;

    w->show();
    app.exec();
    delete w;
    return 0;
}

#include "moc_texttospeechgui.cpp"
