/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateText
{
/*!
 * \brief The TextAutoGenerateTextReplyInfo class represents information about a reply from an LLM.
 *
 * When an LLM generates a completion, the server generally will return some information about the completion, including the
 * duration of the completion, the number of tokens received, and the duration of the prompt evaluation. This struct encapsulates such information.
 * If any one of these fields is not available, it will be set to its default value.
 */
struct TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextReplyInfo {
    enum class ReplyType : uint8_t {
        Unknown = 0,
        Ollama = 1,
        OpenAI = 2,
    };

    //! The total time from when the request was received by the server to when the reply was returned.
    std::chrono::nanoseconds totalDuration = {};

    //! The time spent loading the model.
    std::chrono::nanoseconds loadDuration = {};

    //! The number of tokens in the prompt.
    quint64 promptEvalTokenCount = 0;

    //! The time spent evaluating the prompt.
    std::chrono::nanoseconds promptEvalDuration = {};

    //! The number of tokens in the reply.
    quint64 tokenCount = 0;

    //! The number of completion in the reply.
    quint64 completionTokens = 0;

    //! The number of prompt tokens in the reply.
    quint64 promptTokens = 0;

    //! The time spent generating the reply.
    std::chrono::nanoseconds duration = {};

    ReplyType replyType = ReplyType::Unknown;

    [[nodiscard]] bool isValid() const;

    /*!
     * Serializes the given TextAutoGenerateMessage object.
     * \param msg The TextAutoGenerateMessage to serialize
     * \param toBinary true to serialize to binary format, false for JSON format
     * \return The serialized data as a QByteArray
     */
    [[nodiscard]] static QJsonObject serialize(const TextAutoGenerateTextReplyInfo &msg);
    /*!
     * Deserializes a TextAutoGenerateMessage object from JSON.
     * \param o The JSON object to deserialize from
     * \return The deserialized TextAutoGenerateMessage
     */
    [[nodiscard]] static TextAutoGenerateTextReplyInfo deserialize(const QJsonObject &o);

    /*!
     * \brief generateReplyInfo
     * \return
     */
    [[nodiscard]] QString generateReplyInfo() const;

    /*!
     * \brief generateReplyTypeInfoOllama
     * \return
     */
    [[nodiscard]] QString generateReplyTypeInfoOllama() const;

    /*!
     * \brief generateReplyTypeInfoOpenAI
     * \return
     */
    [[nodiscard]] QString generateReplyTypeInfoOpenAI() const;

    /*!
     * \brief convertReplyTypeToString
     * \param type
     * \return
     */
    [[nodiscard]] static QString convertReplyTypeToString(TextAutoGenerateTextReplyInfo::ReplyType type);

    /*!
     * \brief convertReplyTypeFromString
     * \param str
     * \return
     */
    [[nodiscard]] static TextAutoGenerateTextReplyInfo::ReplyType convertReplyTypeFromString(const QString &str);
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextReplyInfo, Q_RELOCATABLE_TYPE);
/*!
 */
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &t);
