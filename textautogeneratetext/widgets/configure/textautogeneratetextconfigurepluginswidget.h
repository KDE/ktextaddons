/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <TextAddonsWidgets/ConfigurePluginsWidget>
#include <TextAddonsWidgets/PluginUtil>
class KTreeWidgetSearchLineWidget;
class QTreeWidget;
class KMessageWidget;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextConfigurePluginsWidget : public TextAddonsWidgets::ConfigurePluginsWidget
{
    Q_OBJECT
public:
    enum PluginItemData {
        Description = Qt::UserRole + 1,
    };
    explicit TextAutoGenerateTextConfigurePluginsWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextConfigurePluginsWidget() override;

    void save() override;

private:
    void initialize() override;

    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureClicked(const QString &groupName, const QString &identifier);
    TEXTAUTOGENERATETEXT_NO_EXPORT void savePlugins(const QString &groupName, const QString &prefixSettingKey, const QList<PluginItem *> &listItems);
    QList<PluginItem *> mPluginTextItems;
    QList<PluginItem *> mPluginToolsItems;
};
}
