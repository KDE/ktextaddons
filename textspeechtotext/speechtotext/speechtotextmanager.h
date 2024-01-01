/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
namespace TextSpeechToText
{
class SpeechToTextPlugin;
/**
 * @brief The SpeechToTextManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextManager : public QObject
{
    Q_OBJECT
public:
    explicit SpeechToTextManager(QObject *parent = nullptr);
    ~SpeechToTextManager() override;

    void switchEngine(const QString &engineName);

    static SpeechToTextManager *self();

    void speechToText();

    [[nodiscard]] bool hasEngine() const;

Q_SIGNALS:
    void textToSpeechDone(const QString &result);

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void deletePlugin();
    TEXTSPEECHTOTEXT_NO_EXPORT void initializeInput();
    class SpeechToTextPluginPrivate;
    std::unique_ptr<SpeechToTextPluginPrivate> const d;
};
}
