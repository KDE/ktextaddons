/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>
#include <TextAutoGenerateText/TextAutoGenerateQuickAskDialog>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto d = new TextAutoGenerateText::TextAutoGenerateQuickAskDialog(nullptr); // TODO
    d->exec();
    app.exec();
    return 0;
}
