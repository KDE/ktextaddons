/*
   SPDX-FileCopyrightText: 2020 David Faure <faure@kde.org>
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"
#include <QListView>
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::CompletionListView
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/CompletionListView
 */
class TEXTADDONSWIDGETS_EXPORT CompletionListView : public QListView
{
    Q_OBJECT
public:
    /*!
     * \brief CompletionListView
     */
    explicit CompletionListView(QWidget *parent = nullptr);
    /*!
     */
    ~CompletionListView() override;

    /*!
     */
    void setTextWidget(QWidget *textWidget);

    /*!
     */
    void setModel(QAbstractItemModel *model) override;

    /*!
     */
    void slotCompletionAvailable();

Q_SIGNALS:
    /*!
     */
    void complete(const QModelIndex &currentIndex);

protected:
    /*!
     */
    void keyPressEvent(QKeyEvent *event) override;
    /*!
     */
    bool event(QEvent *event) override;

private:
    QWidget *mTextWidget = nullptr;
};
}
