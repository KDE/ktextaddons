/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include "textautogeneratetexttospeechenqueueinfo.h"
#include <QList>
#include <QObject>
namespace TextAutoGenerateText
{
/*!
 * \brief The TextAutoGenerateTextToSpeechEnqueueManager class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToSpeechEnqueueManager : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextToSpeechEnqueueManager(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextToSpeechEnqueueManager() override;

    /*!
     */
    void clear();

    /*!
     * Appends \a info to the queue. The position in the list must match the
     * index of the matching utterance in the text-to-speech queue.
     */
    void insert(const TextAutoGenerateTextToSpeechEnqueueInfo &info);

    /*!
     * Removes the last inserted element. Use it to undo an insert() when
     * enqueuing the text in the text-to-speech engine failed, so that the
     * elements which are still being spoken keep their index.
     */
    void removeLast();

    /*!
     */
    [[nodiscard]] bool contains(const TextAutoGenerateTextToSpeechEnqueueInfo &info) const;

    /*!
     */
    [[nodiscard]] TextAutoGenerateTextToSpeechEnqueueInfo value(qsizetype index) const;

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateTextToSpeechEnqueueInfo> enqueueList() const;

private:
    QList<TextAutoGenerateTextToSpeechEnqueueInfo> mEnqueueList;
};
}
