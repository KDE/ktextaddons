/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QSortFilterProxyModel>
namespace TextAutogenerateText
{
class TextAutoGenerateChatSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    enum class MessageType : uint8_t {
        Unknown,
        All,
        Archived,
        Active,
    };

    explicit TextAutoGenerateChatSortFilterProxyModel(QObject *parent = nullptr);
    ~TextAutoGenerateChatSortFilterProxyModel() override;

    [[nodiscard]] MessageType messageType() const;
    void setMessageType(MessageType newMessageType);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    MessageType mMessageType = MessageType::Unknown;
};
}
