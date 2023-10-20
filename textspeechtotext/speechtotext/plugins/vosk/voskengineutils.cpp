/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskengineutils.h"
#include "libvoskspeechtotext_debug.h"
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

QString VoskEngineUtils::defaultVoskRepository()
{
    return QStringLiteral("https://alphacephei.com/vosk/models/model-list.json");
}

QString VoskEngineUtils::storageLanguagePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QStringLiteral("/vosk-texttospeech");
}

VoskEngineUtils::LanguageInstalled VoskEngineUtils::loadInstalledLanguageInfo(const QString &modelInfoPath)
{
    VoskEngineUtils::LanguageInstalled info;
    QFile file(modelInfoPath + QStringLiteral("/model_info.json"));
    if (!file.open(QFile::ReadOnly)) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to open model_info.json in " << modelInfoPath;
        return info;
    }
    const QByteArray ba = file.readAll();
    const QJsonDocument loadDoc(QJsonDocument::fromJson(ba));
    const QJsonObject o = loadDoc.object();
    info.absoluteLanguageModelPath = o[QLatin1String("absolutePath")].toString();
    info.name = o[QLatin1String("name")].toString();
    info.url = o[QLatin1String("url")].toString();
    info.versionStr = o[QLatin1String("version")].toString();
    return info;
}

bool VoskEngineUtils::createInstalledLanguageInfo(const QString &modelInfoPath, const LanguageInstalled &installed)
{
    QFile file(modelInfoPath + QStringLiteral("/model_info.json"));
    if (!file.open(QFile::WriteOnly)) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to save model_info.json in :" << modelInfoPath;
        return false;
    }
    QJsonDocument d;
    QJsonObject o;
    o[QLatin1String("absolutePath")] = installed.absoluteLanguageModelPath;
    o[QLatin1String("name")] = installed.name;
    o[QLatin1String("url")] = installed.url;
    o[QLatin1String("version")] = installed.versionStr;
    d.setObject(o);
    const QByteArray ba = d.toJson();
    file.write(d.toJson());
    file.close();
    return true;
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
        const VoskEngineUtils::LanguageInstalled info = loadInstalledLanguageInfo(modelLanguagePath);
        if (info.isValid()) {
            languages.append(info);
        }
    }
    return languages;
}

QDebug operator<<(QDebug d, const VoskEngineUtils::LanguageInstalled &t)
{
    d << " shortName " << t.name;
    d << " absoluteLanguageModelPath " << t.absoluteLanguageModelPath;
    d << " version " << t.versionStr;
    d << " url " << t.url;
    return d;
}

bool VoskEngineUtils::LanguageInstalled::operator==(const LanguageInstalled &other) const
{
    return name == other.name && absoluteLanguageModelPath == other.absoluteLanguageModelPath && versionStr == other.versionStr && url == other.url;
}

bool VoskEngineUtils::LanguageInstalled::isValid() const
{
    return !absoluteLanguageModelPath.isEmpty();
}

void VoskEngineUtils::saveSettings()
{
    // TODO
}

void VoskEngineUtils::loadSettings()
{
    // TODO
}

QString VoskEngineUtils::defaultLanguage()
{
    // TODO
    return {};
}
