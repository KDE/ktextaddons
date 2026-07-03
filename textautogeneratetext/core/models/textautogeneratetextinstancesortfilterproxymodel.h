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
 * \class TextAutoGenerateText::TextAutoGenerateTextInstanceSortFilterProxyModel
 * \brief The TextAutoGenerateTextInstanceSortFilterProxyModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstanceSortFilterProxyModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstanceSortFilterProxyModel : public TextAddonsWidgets::SortFilterProxyModelBase
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextInstanceSortFilterProxyModel(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextInstanceSortFilterProxyModel() override;

protected:
    /*!
     */
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};
}
