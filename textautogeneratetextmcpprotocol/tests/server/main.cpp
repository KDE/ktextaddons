/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "servermainwidget.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>
using namespace Qt::Literals::StringLiterals;

int main(int argc, char **argv)
{
    const QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    const QCommandLineOption urlOption(u"url"_s, u"Url where server listens."_s, u"url"_s, u"http://127.0.0.1:8765/mcp"_s);
    parser.addOption(urlOption);
    parser.process(app);

    ServerMainWidget w(parser.value(urlOption));
    w.resize(800, 600);
    w.show();
    w.startServer();
    return app.exec();
}
