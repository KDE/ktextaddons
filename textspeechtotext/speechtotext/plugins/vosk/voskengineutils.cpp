/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskengineutils.h"
#include "libvoskspeechtotext_debug.h"
#include <QDir>
#include <QJsonDocument>
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
    QString newPath = path;
    if (newPath.isEmpty()) {
        newPath = VoskEngineUtils::storageLanguagePath();
    }
    const QDir dir(newPath);
    QVector<VoskEngineUtils::LanguageInstalled> languages;
    const QStringList list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    // qCDebug(LIBVOSKSPEECHTOTEXT_LOG) << " list " << list;
    for (const auto &name : list) {
        // qCDebug(LIBVOSKSPEECHTOTEXT_LOG) << " name " << dir;
        const QString modelLanguagePath{dir.absolutePath() + QLatin1Char('/') + name};
        QFile modelInfoFile(modelLanguagePath + QStringLiteral("/model_info.json"));
        if (!modelInfoFile.exists()) {
            qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "model_info.json not found in " << name;
            return {};
        }
        if (!modelInfoFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to open file " << name;
            return {};
        }

        const QByteArray data = modelInfoFile.readAll();
        modelInfoFile.close();
        const QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
#if 0
        Translator translator;
        translator.parse(jsonResponse.object(), false);
        if (translator.isValid()) {
            // We can't test with isValid() as local info doesn't have url it's logical. // TODO create specific class ???
            // qDebug() << " translator " << translator;
            VoskEngineUtils::LanguageInstalled lang;
            const QString shortName = translator.shortName();
            const QStringList langIdentifier = shortName.split(QLatin1Char('-'));
            if (langIdentifier.count() >= 2) {
                lang.shortName = shortName;
                lang.absoluteLanguageModelPath = modelLanguagePath;
                lang.version = translator.version();
                languages.append(lang);
            }
        }
#endif
    }
    return languages;
}

QDebug operator<<(QDebug d, const VoskEngineUtils::LanguageInstalled &t)
{
    d << " shortName " << t.name;
    d << " absoluteLanguageModelPath " << t.absoluteLanguageModelPath;
    d << " version " << t.versionStr;
    return d;
}

bool VoskEngineUtils::LanguageInstalled::operator==(const LanguageInstalled &other) const
{
    return name == other.name && absoluteLanguageModelPath == other.absoluteLanguageModelPath && versionStr == other.versionStr;
}
