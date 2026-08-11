/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <TextAddonsWidgets/SortFilterProxyModelBase>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextPromptSortFilterProxyModel
 * \brief The TextAutoGenerateTextPromptSortFilterProxyModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextPromptSortFilterProxyModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextPromptSortFilterProxyModel : public TextAddonsWidgets::SortFilterProxyModelBase
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextPromptSortFilterProxyModel(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextPromptSortFilterProxyModel() override;

protected:
    /*!
     */
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};
}
