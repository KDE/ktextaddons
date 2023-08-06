/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "downloadlanguagejob.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QStandardPaths>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("+[file]"), QStringLiteral("Add specific archive file name")));

    parser.process(app);
    if (!parser.positionalArguments().isEmpty()) {
        const QString fileName = parser.positionalArguments().at(0);
        auto download = new DownloadLanguageJob();
        download->setUrl(QUrl(fileName));
        download->start();
    } else {
        qWarning() << "Missing argument";
    }
    app.exec();
    return 0;
}
