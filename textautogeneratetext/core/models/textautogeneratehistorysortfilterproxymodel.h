/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <TextAddonsWidgets/SortFilterProxyModelBase>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateHistorySortFilterProxyModel
 * \brief The TextAutoGenerateHistorySortFilterProxyModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateHistorySortFilterProxyModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateHistorySortFilterProxyModel : public TextAddonsWidgets::SortFilterProxyModelBase
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateHistorySortFilterProxyModel(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateHistorySortFilterProxyModel() override;

    /*!
     */
    [[nodiscard]] bool showArchived() const;
    /*!
     */
    void setShowArchived(bool newShowArchived);

    /*!
     * \brief filterTags
     * \return the tag identifiers a chat must have one of to be shown.
     */
    [[nodiscard]] QList<QByteArray> filterTags() const;
    /*!
     * \brief setFilterTags Only shows the chats which have at least one of \a newFilterTags. An
     * empty list shows every chat.
     */
    void setFilterTags(const QList<QByteArray> &newFilterTags);

protected:
    /*!
     */
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    /*!
     */
    [[nodiscard]] bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    QList<QByteArray> mFilterTags;
    bool mShowArchived = false;
};

}
