/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonscore_export.h"
#include <QSortFilterProxyModel>
namespace TextAddonsCore
{
/*!
 * \class TextAddonsCore::SortFilterProxyModelBase
 * \inmodule TextAddonsCore
 * \inheaderfile TextAddonsCore/SortFilterProxyModelBase
 */
class TEXTADDONSCORE_EXPORT SortFilterProxyModelBase : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for SortFilterProxyModelBase
     * \a parent The parent object
     */
    explicit SortFilterProxyModelBase(QObject *parent = nullptr);
    /*!
     * \brief Destructor for SortFilterProxyModelBase
     */
    ~SortFilterProxyModelBase() override;

    /*!
     * \brief Sets the filter string to \a string. The string is normalized before use.
     */
    void setFilterString(const QString &string);
    /*!
     * \brief Returns true if the normalized \a string contains the filter string,
     * or if the filter string is empty.
     */
    [[nodiscard]] bool contains(const QString &string) const;

protected:
    /*!
     * \brief mFilterString
     */
    QString mFilterString;
};
}
