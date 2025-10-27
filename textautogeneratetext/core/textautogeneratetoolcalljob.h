/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>

namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolPluginJob;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateToolCallJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolCallJob(const QByteArray &chatId,
                                         const QByteArray &uuid,
                                         const QList<TextAutoGenerateReply::ToolCallArgumentInfo> &info,
                                         QObject *parent = nullptr);
    ~TextAutoGenerateToolCallJob() override;
    void start();

    [[nodiscard]] bool canStart() const;

Q_SIGNALS:
    void toolInProgress(const QString &str);
    void finished(const QString &str, const QByteArray &messageUuid, const QByteArray &chatId, const QByteArray &toolIdentifier);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void
    initializeJob(const QByteArray &chatId, const QByteArray &uuid, const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo &info);
    QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *> mListJob;
    const QByteArray mChatId;
    const QByteArray mMessageUuid;
    const QList<TextAutoGenerateReply::ToolCallArgumentInfo> &mInfos;
    QStringList mResult;
};
}
