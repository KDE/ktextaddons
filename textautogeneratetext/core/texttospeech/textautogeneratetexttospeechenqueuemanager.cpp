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

TextAutoGenerateTextToSpeechEnqueueInfo TextAutoGenerateTextToSpeechEnqueueManager::textToSpeechInfo(qsizetype index)
{
    const TextAutoGenerateTextToSpeechEnqueueInfo info = mEnqueueList.take(index);
    return info;
}

bool TextAutoGenerateTextToSpeechEnqueueManager::contains(qsizetype index) const
{
    return mEnqueueList.contains(index);
}

bool TextAutoGenerateTextToSpeechEnqueueManager::contains(const TextAutoGenerateTextToSpeechEnqueueInfo &info) const
{
    for (const auto &[key, value] : mEnqueueList.asKeyValueRange()) {
        if (value == info) {
            return true;
        }
    }
    return false;
}

void TextAutoGenerateTextToSpeechEnqueueManager::insert(qsizetype index, const TextAutoGenerateTextToSpeechEnqueueInfo &info)
{
    if (!info.isValid()) {
        return;
    }
    mEnqueueList.insert(index, info);
}

#include "moc_textautogeneratetexttospeechenqueuemanager.cpp"
