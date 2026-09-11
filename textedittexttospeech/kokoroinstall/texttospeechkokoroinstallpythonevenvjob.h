/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>
namespace TextEditTextToSpeech
{
/*!
 * \brief Creates the python virtual environment used by kokoro.
 *
 * The existing environment is removed first, so that a broken or outdated
 * installation is replaced by a pristine one.
 */
class TextToSpeechKokoroInstallPythonEvenvJob : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroInstallPythonEvenvJob(QObject *parent = nullptr);
    ~TextToSpeechKokoroInstallPythonEvenvJob() override;

    [[nodiscard]] bool canStart() const;

    void start();

Q_SIGNALS:
    void installFailed();
    void installDone();
};
}
