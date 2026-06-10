/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <TextAutoGenerateText/TextAutoGenerateMessageWaitingAnswerAnimationBase>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMessageWaitingAnswerAnimation : public TextAutoGenerateMessageWaitingAnswerAnimationBase
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateMessageWaitingAnswerAnimation(const QByteArray &chatId,
                                                           TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                           QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateMessageWaitingAnswerAnimation() override;
};
}
