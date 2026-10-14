/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "mcpprotocolwidgets_private_export.h"
#include <TextAddonsWidgets/SortFilterProxyModelBase>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
/*!
 * \class TextAutoGenerateTextMcpProtocolWidgets::McpServerSortFilterProxyModel
 * \brief The McpServerSortFilterProxyModel class
 * \author Laurent Montel <montel@kde.org>
 * \internal
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT McpServerSortFilterProxyModel : public TextAddonsWidgets::SortFilterProxyModelBase
{
    Q_OBJECT
public:
    /*!
     */
    explicit McpServerSortFilterProxyModel(QObject *parent = nullptr);
    /*!
     */
    ~McpServerSortFilterProxyModel() override;

protected:
    /*!
     */
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};
}
