/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <TextAddonsWidgets/SortFilterProxyModelBase>
#include <TextAutoGenerateText/TextAutoGenerateTextInstancesManager>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstanceSortFilterProxyModel
 * \brief The TextAutoGenerateTextInstanceSortFilterProxyModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstanceSortFilterProxyModel
 */
class TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateTextInstanceSortFilterProxyModel : public TextAddonsWidgets::SortFilterProxyModelBase
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextInstanceSortFilterProxyModel(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextInstanceSortFilterProxyModel() override;

    /*!
     * \brief instanceFilter
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextInstancesManager::InstanceFilter instanceFilter() const;
    /*!
     * \brief setInstanceFilter
     * \param newInstanceFilter
     */
    void setInstanceFilter(TextAutoGenerateTextInstancesManager::InstanceFilter newInstanceFilter);

protected:
    /*!
     */
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    TextAutoGenerateTextInstancesManager::InstanceFilter mInstanceFilter = TextAutoGenerateTextInstancesManager::InstanceFilter::All;
};
}
