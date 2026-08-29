/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "configurepluginstreewidgetsearchline.h"
#include <QTreeWidgetItem>
#include <TextUtils/ConvertText>
using namespace TextAddonsWidgets;
ConfigurePluginsTreeWidgetSearchLine::ConfigurePluginsTreeWidgetSearchLine(QWidget *parent, QTreeWidget *treeWidget)
    : KTreeWidgetSearchLine(parent, treeWidget)
{
}

ConfigurePluginsTreeWidgetSearchLine::~ConfigurePluginsTreeWidgetSearchLine() = default;

bool ConfigurePluginsTreeWidgetSearchLine::itemMatches(const QTreeWidgetItem *item, const QString &pattern) const
{
    if (pattern.isEmpty()) {
        return true;
    }

    const QString newPattern = TextUtils::ConvertText::normalize(pattern);

    // If the search column list is populated, search just the columns
    // specified.  If it is empty default to searching all of the columns.

    if (const QList<int> columns = searchColumns(); !columns.isEmpty()) {
        QList<int>::ConstIterator it = columns.constBegin();
        for (; it != columns.constEnd(); ++it) {
            if (const QString currentText = TextUtils::ConvertText::normalize(item->text(*it)); *it < item->treeWidget()->columnCount() //
                && currentText.indexOf(newPattern, 0, caseSensitivity()) >= 0) {
                return true;
            }
        }
    } else {
        for (int i = 0; i < item->treeWidget()->columnCount(); i++) {
            if (const QString currentText = TextUtils::ConvertText::normalize(item->text(i)); item->treeWidget()->columnWidth(i) > 0 //
                && currentText.indexOf(newPattern, 0, caseSensitivity()) >= 0) {
                return true;
            }
        }
    }

    return false;
}

#include "moc_configurepluginstreewidgetsearchline.cpp"
