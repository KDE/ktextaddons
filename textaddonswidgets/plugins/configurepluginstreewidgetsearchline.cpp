/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "configurepluginstreewidgetsearchline.h"
#include <QTreeWidget>
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

    const QTreeWidget *const treeWidget = item->treeWidget();
    if (!treeWidget) {
        return false;
    }

    const int columnCount = treeWidget->columnCount();
    const QString newPattern = TextUtils::ConvertText::normalize(pattern);
    const Qt::CaseSensitivity sensitivity = caseSensitivity();

    // If the search column list is populated, search just the columns
    // specified.  If it is empty default to searching all of the columns.

    if (const QList<int> columns = searchColumns(); !columns.isEmpty()) {
        for (const int column : columns) {
            if (column >= columnCount) {
                continue;
            }
            // Normalizing allocates, so only do it for the columns we actually search.
            if (const QString currentText = TextUtils::ConvertText::normalize(item->text(column)); currentText.indexOf(newPattern, 0, sensitivity) >= 0) {
                return true;
            }
        }
    } else {
        for (int i = 0; i < columnCount; ++i) {
            if (treeWidget->columnWidth(i) <= 0) {
                continue;
            }
            if (const QString currentText = TextUtils::ConvertText::normalize(item->text(i)); currentText.indexOf(newPattern, 0, sensitivity) >= 0) {
                return true;
            }
        }
    }

    return false;
}

#include "moc_configurepluginstreewidgetsearchline.cpp"
