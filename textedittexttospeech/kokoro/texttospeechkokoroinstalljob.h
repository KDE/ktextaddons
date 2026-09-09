/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>
namespace TextEditTextToSpeech
{
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

private:
    QStringList mModules;
};
}
