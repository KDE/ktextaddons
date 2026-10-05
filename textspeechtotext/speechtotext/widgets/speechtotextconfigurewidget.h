/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QWidget>
class WhisperSpeechToTextInstallMessageWidget;
namespace TextSpeechToText
{
class SpeechToTextEngineComboBoxWidget;
class SpeechToTextSelectDeviceWidget;
class SpeechToTextLanguageComboBoxWidget;
/**
 * @brief The SpeechToTextConfigureWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief SpeechToTextConfigureWidget
     * \param parent
     */
    explicit SpeechToTextConfigureWidget(QWidget *parent = nullptr);
    /*!
     * \brief ~SpeechToTextConfigureWidget
     */
    ~SpeechToTextConfigureWidget() override;
    /*!
     * \brief loadSettings
     */
    void loadSettings();
    /*!
     * \brief saveSettings
     */
    void saveSettings();

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void slotEngineChanged(const QString &engineName);
    TEXTSPEECHTOTEXT_NO_EXPORT void checkWhisperEngine();
    TEXTSPEECHTOTEXT_NO_EXPORT void slotInstallWhisper(const QStringList &modules);

    SpeechToTextEngineComboBoxWidget *const mSpeechToTextComboBox;
    SpeechToTextSelectDeviceWidget *const mSpeechToTextDevice;
    SpeechToTextLanguageComboBoxWidget *const mSpeechToTextLanguage;
    WhisperSpeechToTextInstallMessageWidget *const mWhisperInstallMessageWidget;
};
}
