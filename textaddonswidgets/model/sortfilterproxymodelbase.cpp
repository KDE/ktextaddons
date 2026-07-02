/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sortfilterproxymodelbase.h"

#include <TextUtils/ConvertText>
using namespace TextAddonsWidgets;
using namespace Qt::Literals::StringLiterals;
SortFilterProxyModelBase::SortFilterProxyModelBase(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

SortFilterProxyModelBase::~SortFilterProxyModelBase() = default;

void SortFilterProxyModelBase::setFilterString(const QString &string)
{
    mFilterString = TextUtils::ConvertText::normalize(string);
    invalidate();
}

bool SortFilterProxyModelBase::contains(const QString &string) const
{
    const QString str = TextUtils::ConvertText::normalize(string);
    return str.contains(mFilterString, Qt::CaseInsensitive);
}

#include "moc_sortfilterproxymodelbase.cpp"
