/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextplugin.h"
using namespace TextSpeechToText;

class TextSpeechToText::SpeechToTextPluginPrivate
{
public:
    QString mResult;
    QString mDefaultLanguage;
};

SpeechToTextPlugin::SpeechToTextPlugin(QObject *parent)
    : QObject{parent}
    , d(new TextSpeechToText::SpeechToTextPluginPrivate())
{
}

SpeechToTextPlugin::~SpeechToTextPlugin() = default;

QString SpeechToTextPlugin::result() const
{
    return d->mResult;
}

QString SpeechToTextPlugin::defaultLanguage() const
{
    return d->mDefaultLanguage;
}

void SpeechToTextPlugin::setDefaultLanguage(const QString &language)
{
    d->mDefaultLanguage = language;
}

#include "moc_speechtotextplugin.cpp"
