/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolBaseJob
 * \brief The TextAutoGenerateTextToolBaseJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolBaseJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolBaseJob : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextToolBaseJob(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextToolBaseJob() override;

    /*!
     */
    virtual void start() = 0;
    /*!
     */
    [[nodiscard]] virtual bool canStart() const;

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> toolArguments() const;
    /*!
     */
    void setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments);

    /*!
     */
    [[nodiscard]] QByteArray messageUuid() const;
    /*!
     */
    void setMessageUuid(const QByteArray &newMessageUuid);

    /*!
     */
    [[nodiscard]] QByteArray toolIdentifier() const;
    /*!
     */
    void setToolIdentifier(const QByteArray &newToolIdentifier);

    /*!
     */
    [[nodiscard]] virtual bool verifyRequiredArguments() const = 0;

    /*!
     */
    [[nodiscard]] QByteArray chatId() const;
    /*!
     */
    void setChatId(const QByteArray &newChatId);

    /*!
     */
    [[nodiscard]] QStringList required() const;
    /*!
     */
    void setRequired(const QStringList &newRequired);

Q_SIGNALS:
    /*!
     */
    void toolInProgress(const QString &info);
    /*!
     */
    void error(const QString &errorStr);

protected:
    QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> mToolArguments;
    QStringList mRequired;
    QByteArray mMessageUuid;
    QByteArray mChatId;
    QByteArray mToolIdentifier;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolBaseJob &t);
