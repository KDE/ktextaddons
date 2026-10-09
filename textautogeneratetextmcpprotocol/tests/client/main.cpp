/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mainwidget.h"
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
    const QCommandLineOption urlOption(u"url"_s, u"Url of MCP server (Streamable HTTP)."_s, u"url"_s, u"http://127.0.0.1:8765/mcp"_s);
    parser.addOption(urlOption);
    const QCommandLineOption autorunOption(u"autorun"_s, u"Run all checks and exit (exit code is 1 if a check failed)."_s);
    parser.addOption(autorunOption);
    parser.process(app);

    MainWidget w(parser.value(urlOption));
    w.resize(900, 600);
    w.show();
    if (parser.isSet(autorunOption)) {
        QObject::connect(&w, &MainWidget::checksFinished, &app, [](int failureCount) {
            QCoreApplication::exit(failureCount == 0 ? 0 : 1);
        });
        w.runAllChecks();
    }
    return app.exec();
}
