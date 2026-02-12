/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QJsonArray>
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextRequest
 * \brief The TextAutoGenerateTextRequest class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextRequest
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextRequest
{
    Q_GADGET
public:
    /*!
     * Constructs a new TextAutoGenerateTextRequest object.
     */
    TextAutoGenerateTextRequest();
    /*!
     * Destroys the TextAutoGenerateTextRequest object.
     */
    ~TextAutoGenerateTextRequest();

    /*!
     * Returns the message text for the request.
     * \return The message as a QString
     */
    [[nodiscard]] QString message() const;
    /*!
     * Sets the message text for the request.
     * \param newMessage The message to set
     */
    void setMessage(const QString &newMessage);

    /*!
     * Compares this request with another for equality.
     * \param other The request to compare with
     * \return true if equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateTextRequest &other) const;

    /*!
     * Returns the model name for the request.
     * \return The model identifier
     */
    [[nodiscard]] QString model() const;
    /*!
     * Sets the model name for the request.
     * \param newModel The model identifier to set
     */
    void setModel(const QString &newModel);

    /*!
     * Returns the message history in JSON format.
     * \return The messages as a QJsonArray
     */
    [[nodiscard]] QJsonArray messages() const;
    /*!
     * Sets the message history in JSON format.
     * \param newMessages The messages to set
     */
    void setMessages(const QJsonArray &newMessages);

    /*!
     * Returns the list of available tools for this request.
     * \return The list of tool identifiers
     */
    [[nodiscard]] QList<QByteArray> tools() const;
    /*!
     * Sets the list of available tools for this request.
     * \param newTools The tool identifiers to set
     */
    void setTools(const QList<QByteArray> &newTools);

private:
    QList<QByteArray> mTools;
    QJsonArray mMessages;
    QString mMessage;
    QString mModel;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextRequest &t);
