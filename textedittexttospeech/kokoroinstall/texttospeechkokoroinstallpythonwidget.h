/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textedittexttospeech_kokoroinstall_private_export.h"
#include <QStringList>
#include <QWidget>
class QPlainTextEdit;
namespace TextEditTextToSpeech
{
class KOKOROINSTALLTEXTTOSPEECH_TESTS_EXPORT TextToSpeechKokoroInstallPythonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroInstallPythonWidget(QWidget *parent = nullptr);
    ~TextToSpeechKokoroInstallPythonWidget() override;

    [[nodiscard]] QStringList modules() const;
    void setModules(const QStringList &newModules);

    void startInstall();

Q_SIGNALS:
    void installDone();
    void installFailed();

private:
    void appendMessage(const QString &message);
    void installModules();

    QPlainTextEdit *const mPlainTextEdit;
    QStringList mModules;
};
}
