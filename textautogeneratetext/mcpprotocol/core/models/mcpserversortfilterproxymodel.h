/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QSortFilterProxyModel>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::McpServerSortFilterProxyModel
 * \brief The McpServerSortFilterProxyModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/McpServerSortFilterProxyModel
 */
class TEXTAUTOGENERATETEXT_EXPORT McpServerSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    /*!
     */
    explicit McpServerSortFilterProxyModel(QObject *parent = nullptr);
    /*!
     */
    ~McpServerSortFilterProxyModel() override;

    /*!
     */
    [[nodiscard]] QString searchText() const;
    /*!
     */
    void setSearchText(const QString &newSearchText);

protected:
    /*!
     */
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QString mSearchText;
};
}
