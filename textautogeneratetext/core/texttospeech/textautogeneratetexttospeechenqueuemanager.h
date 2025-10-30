/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include "textautogeneratetexttospeechenqueueinfo.h"
#include <QMap>
#include <QObject>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToSpeechEnqueueManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToSpeechEnqueueManager(QObject *parent = nullptr);
    ~TextAutoGenerateTextToSpeechEnqueueManager() override;

    void clear();

    [[nodiscard]] TextAutoGenerateTextToSpeechEnqueueInfo textToSpeechInfo(qsizetype index);
    [[nodiscard]] bool contains(qsizetype index) const;
    void insert(qsizetype index, const TextAutoGenerateTextToSpeechEnqueueInfo &info);

    [[nodiscard]] bool contains(const TextAutoGenerateTextToSpeechEnqueueInfo &info) const;

private:
    QMap<qsizetype, TextAutoGenerateTextToSpeechEnqueueInfo> mEnqueueList;
};
}
