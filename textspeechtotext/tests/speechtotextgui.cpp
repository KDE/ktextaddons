/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextgui.h"
#include "speechtotext/widgets/speechtotextconfiguredialog.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QPushButton>
#include <QStandardPaths>
#include <QTextEdit>
#include <QVBoxLayout>
#include <TextSpeechToText/SpeechToTextManager>
#include <TextSpeechToText/SpeechToTextToolButtonWidget>
using namespace Qt::Literals::StringLiterals;
SpeechToTextGui::SpeechToTextGui(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    auto textEdit = new QTextEdit(this);

    auto configureButton = new QPushButton(u"Configure"_s, this);
    connect(configureButton, &QPushButton::clicked, this, [this]() {
        auto w = new TextSpeechToText::SpeechToTextConfigureDialog(this);
        w->exec();
        delete w;
    });

    layout->addWidget(configureButton, 0, Qt::AlignLeft);
    auto speechToTextButton = new TextSpeechToText::SpeechToTextToolButtonWidget(this);
    layout->addWidget(speechToTextButton, 0, Qt::AlignLeft);
    layout->addWidget(textEdit);
    connect(TextSpeechToText::SpeechToTextManager::self(), &TextSpeechToText::SpeechToTextManager::textToSpeechDone, this, [textEdit](const QString &result) {
        textEdit->append(result);
    });
}

SpeechToTextGui::~SpeechToTextGui() = default;

int main(int argc, char **argv)
{
    const QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new SpeechToTextGui();
    w->show();
    app.exec();
    delete w;
    return 0;
}

#include "moc_speechtotextgui.cpp"
