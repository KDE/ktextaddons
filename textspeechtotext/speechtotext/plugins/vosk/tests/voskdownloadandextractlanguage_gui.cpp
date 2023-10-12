/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "downloadlanguagejob.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QFileInfo>
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
        DownloadLanguageJob::DownloadLanguageInfo info;
        info.url = QUrl(fileName);
        const QFileInfo f(fileName);
        const QString baseName = f.baseName();

        info.name = info.url.path() + QLatin1Char('/') + baseName;

        download->setInfo(std::move(info));
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
