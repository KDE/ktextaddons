/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QByteArray>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPluginJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToolPluginJob(QObject *parent = nullptr);
    ~TextAutoGenerateTextToolPluginJob() override;

    virtual void start();
    [[nodiscard]] bool canStart() const;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> toolArguments() const;
    void setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments);

    [[nodiscard]] QStringList requiredArguments() const;
    void setRequiredArguments(const QStringList &newRequiredArguments);

    [[nodiscard]] QByteArray messageUuid() const;
    void setMessageUuid(const QByteArray &newMessageUuid);

    [[nodiscard]] QByteArray toolIdentifier() const;
    void setToolIdentifier(const QByteArray &newToolIdentifier);

    [[nodiscard]] bool verifyRequiredArguments() const;

    [[nodiscard]] QByteArray chatId() const;
    void setChatId(const QByteArray &newChatId);

Q_SIGNALS:
    void finished(const QString &str, const QByteArray &messageUuid, const QByteArray &chatId, const QByteArray &toolIdentifier);

protected:
    QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> mToolArguments;
    QStringList mRequiredArguments;
    QByteArray mMessageUuid;
    QByteArray mChatId;
    QByteArray mToolIdentifier;
};
}
