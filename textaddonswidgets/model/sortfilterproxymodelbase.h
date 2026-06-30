/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QSortFilterProxyModel>
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::SortFilterProxyModelBase
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/SortFilterProxyModelBase
 */
class TEXTADDONSWIDGETS_EXPORT SortFilterProxyModelBase : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for SortFilterProxyModelBase
     * \param parent The parent object
     */
    explicit SortFilterProxyModelBase(QObject *parent = nullptr);
    /*!
     * \brief Destructor for SortFilterProxyModelBase
     */
    ~SortFilterProxyModelBase() override;

    /*!
     * \brief setFilterString
     * \param string
     */
    void setFilterString(const QString &string);
    /*!
     * \brief contains
     * \param string
     * \return
     */
    [[nodiscard]] bool contains(const QString &string) const;

protected:
    /*!
     * \brief mFilterString
     */
    QString mFilterString;
};
}
