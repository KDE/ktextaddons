/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QTextToSpeechPlugin>
namespace TextEditTextToSpeech
{
class TextToSpeechKokoroPlugin : public QObject, public QTextToSpeechPlugin
{
    Q_INTERFACES(QTextToSpeechPlugin)
    Q_PLUGIN_METADATA(IID "org.qt-project.qt.speech.tts.plugin/6.0" FILE "kokoro_plugin.json")
public:
    QTextToSpeechEngine *createTextToSpeechEngine(const QVariantMap &parameters, QObject *parent, QString *errorString) const override;
};
}
