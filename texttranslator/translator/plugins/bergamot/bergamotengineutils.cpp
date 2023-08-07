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
    const QStringList list = dir.entryList(QDir::Dirs);
    for (const auto &name : list) {
        qDebug() << " name " << dir;
        const QFileInfo modelInfo(name + QStringLiteral("/model_info.json"));
        if (!modelInfo.exists()) {
            qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "model_info.json not found in " << name;
            return {};
        }

        QFile modelInfoFile(modelInfo.absoluteFilePath());
        if (!modelInfoFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to open file " << name;
            return {};
        }

        const QByteArray data = modelInfoFile.readAll();
        modelInfoFile.close();
        const QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
        Translator translator;
        translator.parse(jsonResponse.object());
        qDebug() << " translator " << translator;
        if (translator.isValid()) {
            BergamotEngineUtils::LanguageInstalled lang;
            lang.from = translator.source();
            lang.to = translator.target();
            languages.append(lang);
        }
    }
    return languages;
}
