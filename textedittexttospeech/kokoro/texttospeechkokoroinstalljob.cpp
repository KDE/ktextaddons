/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroinstalljob.h"

using namespace TextEditTextToSpeech;
TextToSpeechKokoroInstallJob::TextToSpeechKokoroInstallJob(QObject *parent)
    : QObject{parent}
{
}

TextToSpeechKokoroInstallJob::~TextToSpeechKokoroInstallJob() = default;

bool TextToSpeechKokoroInstallJob::canStart() const
{
    // TODO
    return false;
}

void TextToSpeechKokoroInstallJob::start()
{
    // TODO
    deleteLater();
}

QStringList TextToSpeechKokoroInstallJob::modules() const
{
    return mModules;
}

void TextToSpeechKokoroInstallJob::setModules(const QStringList &newModules)
{
    mModules = newModules;
}

#include "moc_texttospeechkokoroinstalljob.cpp"
