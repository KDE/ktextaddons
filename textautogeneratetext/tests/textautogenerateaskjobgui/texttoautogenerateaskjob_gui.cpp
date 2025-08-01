/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogenerateaskjobwidget.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

int main(int argc, char **argv)
{
    const QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new TextAutoGenerateAskJobWidget;
    w->resize(600, 400);
    w->show();
    app.exec();
    delete w;
    return 0;
}
