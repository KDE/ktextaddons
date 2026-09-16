/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisper_export.h"
#include <KMessageWidget>
#include <QStringList>

/*!
 * \brief Tells that python modules whisper needs are missing, and offers to install them.
 *
 * The missing modules are the ones WhisperSpeechToTextCheckJob reported; the
 * widget only relays the request, the installation itself is done by
 * WhisperSpeechToTextInstallPythonWidget.
 */
class SPEECHTOTEXTWHISPER_EXPORT WhisperSpeechToTextInstallMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextInstallMessageWidget(QWidget *parent = nullptr);
    ~WhisperSpeechToTextInstallMessageWidget() override;

    void setMissingPackages(const QStringList &list);

Q_SIGNALS:
    void installPackages(const QStringList &list);

private:
    QStringList mMissingPackages;
};
