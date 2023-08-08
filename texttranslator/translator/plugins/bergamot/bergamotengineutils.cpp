/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineutils.h"
#include "libbergamot_debug.h"
#include "translator.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDebug>
#include <QJsonDocument>
#include <QStandardPaths>

QString BergamotEngineUtils::defaultBergamotRepository()
{
    return QStringLiteral("https://translatelocally.com/models.json");
}

QString BergamotEngineUtils::groupName()
{
    return QStringLiteral("BergamotTranslator");
}

QString BergamotEngineUtils::coreNumberKey()
{
    return QStringLiteral("CoreNumber");
}

QString BergamotEngineUtils::memoryByThreadKey()
{
    return QStringLiteral("MemoryByThread");
}

QString BergamotEngineUtils::storageLanguagePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QStringLiteral("/bergamot-translator");
}

void BergamotEngineUtils::SettingsInfo::loadSettingsInfo()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), BergamotEngineUtils::groupName());
    numberOfThread = myGroup.readEntry(BergamotEngineUtils::coreNumberKey(), 2);
    memoryByThread = myGroup.readEntry(BergamotEngineUtils::memoryByThreadKey(), 64);
}

void BergamotEngineUtils::SettingsInfo::saveSettingsInfo()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), BergamotEngineUtils::groupName());
    myGroup.writeEntry(BergamotEngineUtils::coreNumberKey(), numberOfThread);
    myGroup.writeEntry(BergamotEngineUtils::memoryByThreadKey(), memoryByThread);
    myGroup.sync();
}

QVector<BergamotEngineUtils::LanguageInstalled> BergamotEngineUtils::languageLocallyStored(const QDir &dir)
{
    QVector<BergamotEngineUtils::LanguageInstalled> languages;
    const QStringList list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    qDebug() << " list " << list;
    for (const auto &name : list) {
        qDebug() << " name " << dir;
        QFile modelInfoFile(dir.absolutePath() + QLatin1Char('/') + name + QStringLiteral("/model_info.json"));
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
            // We can't test with isValid() as local info doesn't have url it's logical. // TODO create specific class ???
            qDebug() << " translator " << translator;
            BergamotEngineUtils::LanguageInstalled lang;
            const QString shortName = translator.shortName();
            const QStringList langIdentifier = shortName.split(QLatin1Char('-'));
            if (langIdentifier.count() >= 2) {
                lang.from = langIdentifier.at(0);
                lang.to = langIdentifier.at(1);
                lang.shortName = shortName;
                languages.append(lang);
            }
        }
    }
    return languages;
}

QDebug operator<<(QDebug d, const BergamotEngineUtils::LanguageInstalled &t)
{
    d << "from " << t.from;
    d << "to " << t.to;
    d << "shortName " << t.shortName;
    return d;
}

bool BergamotEngineUtils::LanguageInstalled::operator==(const LanguageInstalled &other) const
{
    return from == other.from && to == other.to && shortName == other.shortName;
}
