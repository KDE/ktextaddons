/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineutils.h"
using namespace Qt::Literals::StringLiterals;

#include "libbergamot_debug.h"
#include "translator.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDebug>
#include <QJsonDocument>
#include <QStandardPaths>

QString BergamotEngineUtils::defaultBergamotRepository()
{
    return u"https://translatelocally.com/models.json"_s;
}

QString BergamotEngineUtils::groupName()
{
    return u"BergamotTranslator"_s;
}

QString BergamotEngineUtils::coreNumberKey()
{
    return u"CoreNumber"_s;
}

QString BergamotEngineUtils::memoryByThreadKey()
{
    return u"MemoryByThread"_s;
}

QString BergamotEngineUtils::useLocalCacheKey()
{
    return u"UseLocalKey"_s;
}

QString BergamotEngineUtils::storageLanguagePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + u"/bergamot-translator"_s;
}

void BergamotEngineUtils::SettingsInfo::loadSettingsInfo()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), BergamotEngineUtils::groupName());
    numberOfThread = myGroup.readEntry(BergamotEngineUtils::coreNumberKey(), 2);
    memoryByThread = myGroup.readEntry(BergamotEngineUtils::memoryByThreadKey(), 64);
    useLocalCache = myGroup.readEntry(BergamotEngineUtils::useLocalCacheKey(), false);
}

void BergamotEngineUtils::SettingsInfo::saveSettingsInfo()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), BergamotEngineUtils::groupName());
    myGroup.writeEntry(BergamotEngineUtils::coreNumberKey(), numberOfThread);
    myGroup.writeEntry(BergamotEngineUtils::memoryByThreadKey(), memoryByThread);
    myGroup.writeEntry(BergamotEngineUtils::useLocalCacheKey(), useLocalCache);
    myGroup.sync();
}

QVector<BergamotEngineUtils::LanguageInstalled> BergamotEngineUtils::languageLocallyStored(const QString &path)
{
    QString newPath = path;
    if (newPath.isEmpty()) {
        newPath = BergamotEngineUtils::storageLanguagePath();
    }
    QDir dir(newPath);
    QVector<BergamotEngineUtils::LanguageInstalled> languages;
    const QStringList list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    // qCDebug(TRANSLATOR_LIBBERGAMOT_LOG) << " list " << list;
    for (const auto &name : list) {
        // qCDebug(TRANSLATOR_LIBBERGAMOT_LOG) << " name " << dir;
        const QString modelLanguagePath{dir.absolutePath() + u'/' + name};
        QFile modelInfoFile(modelLanguagePath + u"/model_info.json"_s);
        if (!modelInfoFile.exists()) {
            qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "model_info.json not found in " << name;
            return {};
        }
        if (!modelInfoFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to open file " << name;
            return {};
        }

        const QByteArray data = modelInfoFile.readAll();
        modelInfoFile.close();
        const QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
        Translator translator;
        translator.parse(jsonResponse.object(), false);
        if (translator.isValid()) {
            // With slimt we can use only tiny model
            if (translator.type() == QLatin1String("tiny")) {
                // We can't test with isValid() as local info doesn't have url it's logical. // TODO create specific class ???
                // qDebug() << " translator " << translator;
                BergamotEngineUtils::LanguageInstalled lang;
                const QString shortName = translator.shortName();
                const QStringList langIdentifier = shortName.split(u'-');
                if (langIdentifier.count() >= 2) {
                    lang.from = langIdentifier.at(0);
                    lang.to = langIdentifier.at(1);
                    lang.shortName = shortName;
                    lang.absoluteLanguageModelPath = modelLanguagePath;
                    lang.version = translator.version();
                    languages.append(lang);
                }
            }
        }
    }
    return languages;
}

QDebug operator<<(QDebug d, const BergamotEngineUtils::LanguageInstalled &t)
{
    d << " from " << t.from;
    d << " to " << t.to;
    d << " shortName " << t.shortName;
    d << " absoluteLanguageModelPath " << t.absoluteLanguageModelPath;
    d << " version " << t.version;
    return d;
}

bool BergamotEngineUtils::LanguageInstalled::operator==(const LanguageInstalled &other) const
{
    return from == other.from && to == other.to && shortName == other.shortName && absoluteLanguageModelPath == other.absoluteLanguageModelPath
        && version == other.version;
}
