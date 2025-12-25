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
/**
 * @brief The TextAutoGenerateTextToSpeechEnqueueManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToSpeechEnqueueManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToSpeechEnqueueManager(QObject *parent = nullptr);
    ~TextAutoGenerateTextToSpeechEnqueueManager() override;

    void clear();

    void insert(const TextAutoGenerateTextToSpeechEnqueueInfo &info);

    [[nodiscard]] bool contains(const TextAutoGenerateTextToSpeechEnqueueInfo &info) const;

    [[nodiscard]] TextAutoGenerateTextToSpeechEnqueueInfo value(qsizetype index);

    [[nodiscard]] QList<TextAutoGenerateTextToSpeechEnqueueInfo> enqueueList() const;

private:
    QList<TextAutoGenerateTextToSpeechEnqueueInfo> mEnqueueList;
};
}
