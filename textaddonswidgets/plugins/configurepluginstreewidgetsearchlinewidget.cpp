/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginstreewidgetsearchlinewidget.h"

using namespace TextAddonsWidgets;

ConfigurePluginsTreeWidgetSearchLineWidget::ConfigurePluginsTreeWidgetSearchLineWidget(QWidget *parent, QTreeWidget *treeWidget)
    : KTreeWidgetSearchLineWidget(parent, treeWidget)
{
}

ConfigurePluginsTreeWidgetSearchLineWidget::~ConfigurePluginsTreeWidgetSearchLineWidget() = default;

KTreeWidgetSearchLine *ConfigurePluginsTreeWidgetSearchLineWidget::createSearchLine(QTreeWidget *treeWidget) const
{
    // TODO
    return KTreeWidgetSearchLineWidget::createSearchLine(treeWidget);
}
