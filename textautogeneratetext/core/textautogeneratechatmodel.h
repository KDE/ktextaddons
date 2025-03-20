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
    enum ChatRole : uint8_t {
        MessageRole,
        SenderRole,
        FinishedRole,
    };

    explicit TextAutoGenerateChatModel(QObject *parent = nullptr);
    ~TextAutoGenerateChatModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QList<TextAutoGenerateMessage> messages() const;
    void setMessages(const QList<TextAutoGenerateMessage> &newMessages);

    void resetConversation();

    void addMessage(const TextAutoGenerateMessage &msg);

private:
    QList<TextAutoGenerateMessage> mMessages;
};
}
