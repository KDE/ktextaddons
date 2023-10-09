/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskengineutils.h"
#include <QDir>
#include <QStandardPaths>

QString VoskEngineUtils::defaultVoskRepository()
{
    return QStringLiteral("https://alphacephei.com/vosk/models/model-list.json");
}

QString VoskEngineUtils::storageLanguagePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QStringLiteral("/vosk-texttospeech");
}

QVector<VoskEngineUtils::LanguageInstalled> VoskEngineUtils::languageLocallyStored(const QString &path)
{
#if 0
    QString newPath = path;
    if (newPath.isEmpty()) {
        newPath = VoskEngineUtils::storageLanguagePath();
    }
    QDir dir(newPath);
    QVector<VoskEngineUtils::LanguageInstalled> languages;
    const QStringList list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    // qCDebug(TRANSLATOR_LIBBERGAMOT_LOG) << " list " << list;
    for (const auto &name : list) {
        // qCDebug(TRANSLATOR_LIBBERGAMOT_LOG) << " name " << dir;
        const QString modelLanguagePath{dir.absolutePath() + QLatin1Char('/') + name};
        QFile modelInfoFile(modelLanguagePath + QStringLiteral("/model_info.json"));
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
            // qDebug() << " translator " << translator;
            BergamotEngineUtils::LanguageInstalled lang;
            const QString shortName = translator.shortName();
            const QStringList langIdentifier = shortName.split(QLatin1Char('-'));
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
    return languages;
#endif
    return {};
}

QDebug operator<<(QDebug d, const VoskEngineUtils::LanguageInstalled &t)
{
    d << " shortName " << t.shortName;
    d << " absoluteLanguageModelPath " << t.absoluteLanguageModelPath;
    d << " version " << t.version;
    return d;
}

bool VoskEngineUtils::LanguageInstalled::operator==(const LanguageInstalled &other) const
{
    return shortName == other.shortName && absoluteLanguageModelPath == other.absoluteLanguageModelPath && version == other.version;
}
