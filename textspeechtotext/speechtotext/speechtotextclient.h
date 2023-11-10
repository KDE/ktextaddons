/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
namespace TextSpeechToText
{
class SpeechToTextPlugin;
/**
 * @brief The SpeechToTextClient class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextClient : public QObject
{
    Q_OBJECT
public:
    enum EngineType {
        Locale,
        Network,
    };
    explicit SpeechToTextClient(QObject *parent = nullptr);
    ~SpeechToTextClient() override;

    /**
     * @returns the name of the implementing class.
     */
    virtual QString name() const = 0;

    virtual QString translatedName() const = 0;

    virtual SpeechToTextPlugin *createTextToSpeech() = 0;

    [[nodiscard]] virtual bool hasConfigurationDialog() const;

    virtual bool showConfigureDialog(QWidget *parentWidget);

    [[nodiscard]] virtual TextSpeechToText::SpeechToTextClient::EngineType engineType() const = 0;

Q_SIGNALS:
    void configureChanged();
};
}
Q_DECLARE_INTERFACE(TextSpeechToText::SpeechToTextClient, "org.kde.texttospeech.Client")
