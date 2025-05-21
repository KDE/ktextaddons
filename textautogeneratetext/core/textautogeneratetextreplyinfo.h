/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateTextReplyInfo class represents information about a reply from an LLM.
 *
 * When an LLM generates a completion, the server generally will return some information about the completion, including the
 * duration of the completion, the number of tokens received, and the duration of the prompt evaluation. This struct encapsulates such information.
 * If any one of these fields is not available, it will be set to its default value.
 */
struct TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextReplyInfo {
    //! The total time from when the request was received by the server to when the reply was returned.
    std::chrono::nanoseconds totalDuration = {};

    //! The time spent loading the model.
    std::chrono::nanoseconds loadDuration = {};

    //! The number of tokens in the prompt.
    int promptEvalTokenCount = 0;

    //! The time spent evaluating the prompt.
    std::chrono::nanoseconds promptEvalDuration = {};

    //! The number of tokens in the reply.
    int tokenCount = 0;

    //! The time spent generating the reply.
    std::chrono::nanoseconds duration = {};
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextReplyInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &t);
