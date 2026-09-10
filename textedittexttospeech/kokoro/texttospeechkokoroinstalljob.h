/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QProcess>
#include <QStringList>
namespace TextEditTextToSpeech
{
/*!
 * \brief Installs the python modules needed by kokoro in the venv.
 *
 * The modules are installed one after the other with the pip of the venv,
 * torch being taken from the cpu-only index so that the whole cuda stack is
 * not downloaded.
 */
class TextToSpeechKokoroInstallJob : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroInstallJob(QObject *parent = nullptr);
    ~TextToSpeechKokoroInstallJob() override;

    [[nodiscard]] bool canStart() const;

    void start();

    [[nodiscard]] QStringList modules() const;
    void setModules(const QStringList &newModules);

Q_SIGNALS:
    void installDone();
    void installFailed();
    /*! Output of pip, so that the progress can be shown to the user. */
    void installMessage(const QString &message);

private:
    void installNextModule();
    void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void failed(const QString &errorMessage);

    QStringList mModules;
    QStringList mRemainingModules;
    QProcess *mProcess = nullptr;
};
}
