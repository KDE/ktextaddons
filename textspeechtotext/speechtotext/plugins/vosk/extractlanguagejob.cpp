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

void ExtractLanguageJob::extractRecursive(const KArchiveDirectory *dir, const QString &path)
{
    // qDebug() << " path " << path;
    const QStringList lst = dir->entries();
    // qDebug() << " list entries : " << lst;
    for (const QString &it : lst) {
        const KArchiveEntry *entry = dir->entry(it);
        if (entry->isDirectory()) {
            // qDebug() << " directory ********" << it << "sss " << (path + it + QLatin1Char('/'));
            extractRecursive(static_cast<const KArchiveDirectory *>(entry), path + it + QLatin1Char('/'));
        } else if (entry->isFile()) {
            const KArchiveEntry *filePathEntry = dir->entry(it);
            const auto filePath = static_cast<const KArchiveFile *>(filePathEntry);
            const QString storeDirectory{VoskEngineUtils::storageLanguagePath() + QLatin1Char('/') + path};
            // qDebug() << "storeDirectory  " << storeDirectory << " ddd " << it;
            if (!QDir().mkpath(storeDirectory)) {
                qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to create :" << storeDirectory;
                continue;
            }
            if (!filePath->copyTo(storeDirectory)) {
                qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to copy to " << storeDirectory;
            }
        }
    }
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
    extractRecursive(zipDir, QString());
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
