/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratetexttospeechenqueuemanager.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToSpeechEnqueueManager::TextAutoGenerateTextToSpeechEnqueueManager(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToSpeechEnqueueManager::~TextAutoGenerateTextToSpeechEnqueueManager() = default;

void TextAutoGenerateTextToSpeechEnqueueManager::clear()
{
    mEnqueueList.clear();
}

TextAutoGenerateTextToSpeechEnqueueInfo TextAutoGenerateTextToSpeechEnqueueManager::value(qsizetype index)
{
    return mEnqueueList.value(index);
}

QList<TextAutoGenerateTextToSpeechEnqueueInfo> TextAutoGenerateTextToSpeechEnqueueManager::enqueueList() const
{
    return mEnqueueList;
}

bool TextAutoGenerateTextToSpeechEnqueueManager::contains(const TextAutoGenerateTextToSpeechEnqueueInfo &info) const
{
    // we can have several invalid element. Necessary if we don't have info.
    if (!info.isValid()) {
        return false;
    }
    return mEnqueueList.contains(info);
}

void TextAutoGenerateTextToSpeechEnqueueManager::insert(const TextAutoGenerateTextToSpeechEnqueueInfo &info)
{
    mEnqueueList.append(info);
}

#include "moc_textautogeneratetexttospeechenqueuemanager.cpp"
