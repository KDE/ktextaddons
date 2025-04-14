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
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChatRole : uint16_t {
        MessageRole = Qt::UserRole + 1,
        SenderRole,
        FinishedRole,
        DateTimeRole,
        UuidRole,
    };

    explicit TextAutoGenerateChatModel(QObject *parent = nullptr);
    ~TextAutoGenerateChatModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QList<TextAutoGenerateMessage> messages() const;
    void setMessages(const QList<TextAutoGenerateMessage> &newMessages);

    void resetConversation();

    void addMessage(const TextAutoGenerateMessage &msg);

    void replaceLastMessage(const TextAutoGenerateMessage &msg);

    [[nodiscard]] TextAutoGenerateMessage lastMessage() const;

private:
    QList<TextAutoGenerateMessage> mMessages;
};
}
