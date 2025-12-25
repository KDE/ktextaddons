/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateSearchMessagesModel class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateSearchMessagesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MessageSearchRoles : uint16_t {
        ChatUuid = Qt::UserRole + 1,
        MessageUuid,
        PreviewText,
        DateTime,
    };

    explicit TextAutoGenerateSearchMessagesModel(QObject *parent = nullptr);
    ~TextAutoGenerateSearchMessagesModel() override;

    [[nodiscard]] QList<TextAutoGenerateSearchMessage> searchMessages() const;
    void setSearchMessages(const QList<TextAutoGenerateSearchMessage> &newSearchMessages);

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool isEmpty() const;

private:
    QList<TextAutoGenerateSearchMessage> mSearchMessages;
};
}
