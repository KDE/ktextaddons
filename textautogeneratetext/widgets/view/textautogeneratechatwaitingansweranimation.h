/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratemessagewaitingansweranimationbase.h"
#include "textautogeneratetext_private_export.h"

namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateChatWaitingAnswerAnimation : public TextAutoGenerateMessageWaitingAnswerAnimationBase
{
    Q_OBJECT
public:
    explicit TextAutoGenerateChatWaitingAnswerAnimation(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    ~TextAutoGenerateChatWaitingAnswerAnimation() override;
};
}
