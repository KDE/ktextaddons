/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtexteditor/richtexteditorwidget.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);

    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new TextCustomEditor::RichTextEditorWidget();
    w->resize(800, 600);
    w->show();
    app.exec();
    delete w;
    return 0;
}
