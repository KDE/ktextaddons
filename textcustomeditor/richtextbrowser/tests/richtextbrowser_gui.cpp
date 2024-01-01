/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowser/richtextbrowserwidget.h"

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

    auto w = new TextCustomEditor::RichTextBrowserWidget();
    w->setPlainText(QStringLiteral("Test RichTextBrowserWidget"));
    w->resize(800, 600);
    w->show();
    app.exec();
    delete w;
    return 0;
}
