/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "configurepluginstreewidgetsearchline.h"

using namespace TextAddonsWidgets;
ConfigurePluginsTreeWidgetSearchLine::ConfigurePluginsTreeWidgetSearchLine(QWidget *parent, QTreeWidget *treeWidget)
    : KTreeWidgetSearchLine(parent, treeWidget)
{
}

ConfigurePluginsTreeWidgetSearchLine::~ConfigurePluginsTreeWidgetSearchLine() = default;

bool ConfigurePluginsTreeWidgetSearchLine::itemMatches(const QTreeWidgetItem *item, const QString &pattern) const
{
    // TODO
    return false;
}
