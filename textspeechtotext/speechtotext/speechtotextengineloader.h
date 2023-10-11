/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textspeechtotext_export.h"
#include <QObject>
#include <memory>
namespace TextSpeechToText
{
class SpeechToTextEngineLoaderPrivate;
class SpeechToTextClient;
/**
 * @brief The SpeechToTextEngineLoader class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextEngineLoader : public QObject
{
    Q_OBJECT
public:
    static SpeechToTextEngineLoader *self();

    explicit SpeechToTextEngineLoader(QObject *parent = nullptr);
    ~SpeechToTextEngineLoader() override;

    Q_REQUIRED_RESULT TextSpeechToText::SpeechToTextClient *createSpeechToTextClient(const QString &clientName);

    Q_REQUIRED_RESULT bool hasConfigurationDialog(const QString &clientName) const;

    Q_REQUIRED_RESULT bool showConfigureDialog(const QString &clientName, QWidget *parentWidget);

    Q_REQUIRED_RESULT QMap<QString, QString> speechToTextEngineInfos() const;

    Q_REQUIRED_RESULT QString fallbackFirstEngine() const;

Q_SIGNALS:
    void loadingSpeechToTextFailed();
    void noPluginsFound();

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void loadPlugins();
    TEXTSPEECHTOTEXT_NO_EXPORT void loadPlugin(const QString &pluginPath);
    std::unique_ptr<SpeechToTextEngineLoaderPrivate> const d;
};
}
