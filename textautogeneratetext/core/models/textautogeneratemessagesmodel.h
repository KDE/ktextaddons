/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <QJsonArray>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateChatModel class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMessagesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MessageRoles : uint16_t {
        MessageRole = Qt::UserRole + 1,
        SenderRole,
        FinishedRole,
        DateTimeRole,
        DateTimeStrRole,
        UuidRole,
        MouseHoverRole,
        EditingRole,
        WaitingAnswerRole,
        ModelInfoRole,
        OriginalMessageRole,
    };

    explicit TextAutoGenerateMessagesModel(QObject *parent = nullptr);
    ~TextAutoGenerateMessagesModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    [[nodiscard]] QList<TextAutoGenerateMessage> messages() const;
    void setMessages(const QList<TextAutoGenerateMessage> &newMessages);

    [[nodiscard]] TextAutoGenerateMessage message(const QByteArray &uuid) const;

    [[nodiscard]] QModelIndex refreshAnswer(const QByteArray &uuid) const;

    void resetConversation();

    void addMessage(const TextAutoGenerateMessage &msg);

    [[nodiscard]] QList<QByteArray> removeDiscussion(const QByteArray &uuid);

    void replaceContent(const QByteArray &uuid, const QString &content);
    void changeInProgress(const QByteArray &uuid, bool inProgress);
    [[nodiscard]] QByteArray editMessage(const QByteArray &uuid, const QString &str);
    [[nodiscard]] QModelIndex indexForUuid(const QByteArray &uuid) const;
    [[nodiscard]] bool cancelRequest(const QModelIndex &index);

    [[nodiscard]] QByteArray chatId() const;
    void setChatId(const QByteArray &newChatId);

    [[nodiscard]] QJsonArray convertToOllamaChat() const;

Q_SIGNALS:
    void conversationCleared();

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT bool waitingAnswer(const TextAutoGenerateMessage &message) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QString generateModelInfo(const TextAutoGenerateMessage &m) const;
    QList<TextAutoGenerateMessage> mMessages;
    QByteArray mChatId;
};
}
