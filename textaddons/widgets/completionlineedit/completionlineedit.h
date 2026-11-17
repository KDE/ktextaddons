/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QLineEdit>

#include "textaddonswidgets_export.h"

class QAbstractItemModel;
namespace TextAddonsWidgets
{
class CompletionListView;
/*!
 * \class TextAddonsWidgets::CompletionLineEdit
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/CompletionLineEdit
 */
class TEXTADDONSWIDGETS_EXPORT CompletionLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    /*!
     */
    explicit CompletionLineEdit(QWidget *parent = nullptr);
    /*!
     */
    ~CompletionLineEdit() override;

    /*!
     */
    void setCompletionModel(QAbstractItemModel *model);

Q_SIGNALS:
    /*!
     */
    void complete(const QModelIndex &index);

protected:
    CompletionListView *const mCompletionListView;
};
}
