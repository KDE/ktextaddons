/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "downloadlanguagejob.h"
using namespace Qt::Literals::StringLiterals;

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
    parser.addOption(QCommandLineOption(QStringList() << u"+[file]"_s, u"Add specific archive file name"_s));

    parser.process(app);
    if (!parser.positionalArguments().isEmpty()) {
        const QString fileName = parser.positionalArguments().at(0);
        auto download = new DownloadLanguageJob();
        download->setUrl(QUrl(fileName));
        QObject::connect(download, &DownloadLanguageJob::extractDone, &app, []() {
            qDebug() << "Extraction Done";
        });
        QObject::connect(download, &DownloadLanguageJob::errorText, &app, [](const QString &str) {
            qDebug() << "Extraction error: " << str;
        });
        download->start();
        app.exec();
    } else {
        qWarning() << "Missing argument";
    }
    return 0;
}
