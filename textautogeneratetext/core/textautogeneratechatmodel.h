/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratemessage.h"
#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
namespace TextAutogenerateText
{
/**
 * @brief The TextAutoGenerateChatModel class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChatRoles : uint16_t {
        MessageRole = Qt::UserRole + 1,
        SenderRole,
        FinishedRole,
        DateTimeRole,
        DateTimeStrRole,
        UuidRole,
        TopicRole,
        MouseHoverRole,
    };

    explicit TextAutoGenerateChatModel(QObject *parent = nullptr);
    ~TextAutoGenerateChatModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    [[nodiscard]] QList<TextAutoGenerateMessage> messages() const;
    void setMessages(const QList<TextAutoGenerateMessage> &newMessages);

    void resetConversation();

    void addMessage(const TextAutoGenerateMessage &msg);

    void replaceLastMessage(const TextAutoGenerateMessage &msg);

    [[nodiscard]] TextAutoGenerateMessage lastMessage() const;

    void removeDiscussion(const QByteArray &uuid);

Q_SIGNALS:
    void conversationCleared();

private:
    QList<TextAutoGenerateMessage> mMessages;
};
}
