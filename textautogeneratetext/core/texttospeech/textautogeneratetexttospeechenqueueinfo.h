/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextcore_private_export.h"

#include <QByteArray>
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \brief The TextAutoGenerateTextToSpeechEnqueueInfo class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXTCORE_EXPORT TextAutoGenerateTextToSpeechEnqueueInfo
{
public:
    /*!
     */
    TextAutoGenerateTextToSpeechEnqueueInfo();

    /*!
     */
    [[nodiscard]] QByteArray chatId() const;
    /*!
     */
    void setChatId(const QByteArray &newChatId);

    /*!
     */
    [[nodiscard]] QByteArray messageId() const;
    /*!
     */
    void setMessageId(const QByteArray &newMessageId);

    /*!
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateTextToSpeechEnqueueInfo &other) const;
    /*!
     */
    [[nodiscard]] bool isValid() const;

private:
    QByteArray mChatId;
    QByteArray mMessageId;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextToSpeechEnqueueInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToSpeechEnqueueInfo &t);
