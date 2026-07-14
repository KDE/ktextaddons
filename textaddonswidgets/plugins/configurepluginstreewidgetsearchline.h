/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <KTreeWidgetSearchLine>
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT ConfigurePluginsTreeWidgetSearchLine : public KTreeWidgetSearchLine
{
    Q_OBJECT
public:
    explicit ConfigurePluginsTreeWidgetSearchLine(QWidget *parent = nullptr, QTreeWidget *treeWidget = nullptr);
    ~ConfigurePluginsTreeWidgetSearchLine() override;

protected:
    [[nodiscard]] bool itemMatches(const QTreeWidgetItem *item, const QString &pattern) const override;
};
}
