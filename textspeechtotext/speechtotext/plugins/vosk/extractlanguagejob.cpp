/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "extractlanguagejob.h"
#include "libvoskspeechtotext_debug.h"
#include "voskengineutils.h"
#include <KLocalizedString>
#include <KZip>
#include <QDir>

ExtractLanguageJob::ExtractLanguageJob(QObject *parent)
    : QObject{parent}
{
}

ExtractLanguageJob::~ExtractLanguageJob() = default;

bool ExtractLanguageJob::canStart() const
{
    return !mSource.isEmpty();
}

void ExtractLanguageJob::start()
{
    if (!canStart()) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to start ExtractLanguageJob";
        Q_EMIT errorText(i18n("Impossible to extract language"));
        Q_EMIT finished();
        deleteLater();
        return;
    }
    auto zip = new KZip(mSource);
    if (!zip->open(QIODevice::ReadOnly)) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to open temporary file" << mSource;
        Q_EMIT finished();
        deleteLater();
        return;
    }
    if (!QDir().mkpath(VoskEngineUtils::storageLanguagePath())) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to create path" << VoskEngineUtils::storageLanguagePath();
        Q_EMIT finished();
        deleteLater();
        return;
    }
    const KArchiveDirectory *zipDir = zip->directory();
    const QStringList lst = zipDir->entries();
    qDebug() << " list of files " << lst;
    for (const QString &name : lst) {
        const QString storeDirectory{VoskEngineUtils::storageLanguagePath() + QLatin1Char('/') + name};
        qDebug() << " storeDirectory " << storeDirectory;
        if (!QDir().mkpath(storeDirectory)) {
            qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to create :" << storeDirectory;
            continue;
        }
        const KArchiveEntry *configPathEntry = zipDir->entry(name);
        if (configPathEntry && configPathEntry->isDirectory()) {
            const auto configDirectory = static_cast<const KArchiveDirectory *>(configPathEntry);
            const QStringList entries = configDirectory->entries();
            qDebug() << " list of files entries " << entries;
            for (const QString &file : entries) {
                const KArchiveEntry *filePathEntry = zipDir->entry(name + QStringLiteral("/%1").arg(file));
                if (filePathEntry) {
                    if (filePathEntry->isFile()) {
                        const auto filePath = static_cast<const KArchiveFile *>(filePathEntry);
                        if (!filePath->copyTo(storeDirectory)) {
                            qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to copy to " << storeDirectory;
                        }
                    } else if (filePathEntry->isDirectory()) {
                        const auto directoryPath = static_cast<const KArchiveDirectory *>(filePathEntry);
                        const QString newPath = storeDirectory + QLatin1Char('/') + directoryPath->name();
                        qDebug() << " newPath " << newPath;
                        if (!directoryPath->copyTo(newPath)) {
                            qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to copy to " << storeDirectory;
                        }
                    }
                } else {
                    qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to import file " << file;
                }
            }
        }
    }
    delete zip;
    Q_EMIT finished();
    deleteLater();
}

QString ExtractLanguageJob::source() const
{
    return mSource;
}

void ExtractLanguageJob::setSource(const QString &newSource)
{
    mSource = newSource;
}

#include "moc_extractlanguagejob.cpp"
