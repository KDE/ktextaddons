/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "extractlanguagejob.h"
#include "bergamotengineutils.h"
#include "libbergamot_debug.h"
#include <KLocalizedString>
#include <KTar>
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
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to start ExtractLanguageJob";
        Q_EMIT errorText(i18n("Impossible to extract language"));
        deleteLater();
        return;
    }
    auto tar = new KTar(mSource);
    if (!tar->open(QIODevice::ReadOnly)) {
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to open temporary file" << mSource;
        deleteLater();
        return;
    }
    if (!QDir().mkpath(BergamotEngineUtils::storageLanguagePath())) {
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to create path" << BergamotEngineUtils::storageLanguagePath();
        deleteLater();
        return;
    }
    const KArchiveDirectory *zipDir = tar->directory();
    const QStringList lst = zipDir->entries();
    // qDebug() << " list of files " << lst;
    for (const QString &name : lst) {
        const QString storeDirectory{BergamotEngineUtils::storageLanguagePath() + QLatin1Char('/') + name};
        if (!QDir().mkpath(storeDirectory)) {
            qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to create :" << storeDirectory;
            continue;
        }
        const KArchiveEntry *configPathEntry = zipDir->entry(name);
        if (configPathEntry && configPathEntry->isDirectory()) {
            const auto configDirectory = static_cast<const KArchiveDirectory *>(configPathEntry);
            const QStringList entries = configDirectory->entries();
            // qDebug() << " list of files entries " << entries;
            for (const QString &file : entries) {
                const KArchiveEntry *filePathEntry = zipDir->entry(name + QStringLiteral("/%1").arg(file));
                if (filePathEntry && filePathEntry->isFile()) {
                    const auto filePath = static_cast<const KArchiveFile *>(filePathEntry);
                    if (!filePath->copyTo(storeDirectory)) {
                        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to copy to " << storeDirectory;
                    }
                } else {
                    qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to import file " << file;
                }
            }
        }
    }
    delete tar;
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
