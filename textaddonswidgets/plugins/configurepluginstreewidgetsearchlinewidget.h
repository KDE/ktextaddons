/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"
#include <KTreeWidgetSearchLineWidget>
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT ConfigurePluginsTreeWidgetSearchLineWidget : public KTreeWidgetSearchLineWidget
{
    Q_OBJECT
public:
    explicit ConfigurePluginsTreeWidgetSearchLineWidget(QWidget *parent = nullptr, QTreeWidget *treeWidget = nullptr);
    ~ConfigurePluginsTreeWidgetSearchLineWidget() override;

protected:
    KTreeWidgetSearchLine *createSearchLine(QTreeWidget *treeWidget) const override;
};
}
