/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QSortFilterProxyModel>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateHistorySortFilterProxyModel
 * \brief The TextAutoGenerateHistorySortFilterProxyModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateHistorySortFilterProxyModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateHistorySortFilterProxyModel : public QSortFilterProxyModel
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

protected:
    /*!
     */
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    /*!
     */
    [[nodiscard]] bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool mShowArchived = false;
};

}
