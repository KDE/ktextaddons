/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginProperty>
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

    [[nodiscard]] QByteArray messageUuid() const;
    void setMessageUuid(const QByteArray &newMessageUuid);

    [[nodiscard]] QByteArray toolIdentifier() const;
    void setToolIdentifier(const QByteArray &newToolIdentifier);

    [[nodiscard]] bool verifyRequiredArguments() const;

    [[nodiscard]] QByteArray chatId() const;
    void setChatId(const QByteArray &newChatId);

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> properties() const;
    void setProperties(const QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> &newProperties);

Q_SIGNALS:
    void finished(const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &info);
    void toolInProgress(const QString &info);

protected:
    QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> mProperties;
    QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> mToolArguments;
    QByteArray mMessageUuid;
    QByteArray mChatId;
    QByteArray mToolIdentifier;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolPluginJob &t);
