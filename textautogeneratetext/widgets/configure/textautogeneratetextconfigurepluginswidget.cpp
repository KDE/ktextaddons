/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfigurepluginswidget.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/plugintext/textautogenerateplugintextmanager.h"
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGeneratePluginText>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateTextConfigurePluginsWidget::TextAutoGenerateTextConfigurePluginsWidget(QWidget *parent)
    : TextAddonsWidgets::ConfigurePluginsWidget{parent}
{
    connect(this, &TextAutoGenerateTextConfigurePluginsWidget::configureClicked, this, &TextAutoGenerateTextConfigurePluginsWidget::slotConfigureClicked);
}

TextAutoGenerateTextConfigurePluginsWidget::~TextAutoGenerateTextConfigurePluginsWidget() = default;

void TextAutoGenerateTextConfigurePluginsWidget::save()
{
    savePlugins(TextAutoGeneratePluginTextManager::self()->configGroupName(),
                TextAutoGeneratePluginTextManager::self()->configPrefixSettingKey(),
                mPluginTextItems);

    savePlugins(TextAutoGenerateTextToolPluginManager::self()->configGroupName(),
                TextAutoGenerateTextToolPluginManager::self()->configPrefixSettingKey(),
                mPluginToolsItems);
}

[[nodiscard]] static QString textPluginGroupName()
{
    return u"pluginTextPluginGroupName"_s;
}

[[nodiscard]] static QString toolPluginGroupName()
{
    return u"pluginToolPluginGroupName"_s;
}

void TextAutoGenerateTextConfigurePluginsWidget::initialize()
{
    mTreePluginWidget->clear();
    // Disable sorting before filling list
    mTreePluginWidget->setSortingEnabled(false);
    fillTopItems(TextAutoGeneratePluginTextManager::self()->pluginDataList(),
                 i18n("Text Plugins"),
                 TextAutoGeneratePluginTextManager::self()->configGroupName(),
                 TextAutoGeneratePluginTextManager::self()->configPrefixSettingKey(),
                 mPluginTextItems,
                 textPluginGroupName());

    fillTopItems(TextAutoGenerateTextToolPluginManager::self()->pluginDataList(),
                 i18n("Tool Plugins"),
                 TextAutoGenerateTextToolPluginManager::self()->configGroupName(),
                 TextAutoGenerateTextToolPluginManager::self()->configPrefixSettingKey(),
                 mPluginToolsItems,
                 toolPluginGroupName());
    // Re-enable it
    mTreePluginWidget->setSortingEnabled(true);
    mTreePluginWidget->expandAll();
}

void TextAutoGenerateTextConfigurePluginsWidget::slotConfigureClicked(const QString &groupName, const QString &identifier)
{
    if (!groupName.isEmpty() && !identifier.isEmpty()) {
        if (groupName == textPluginGroupName()) {
            const auto p = TextAutoGeneratePluginTextManager::self()->pluginFromIdentifier(identifier);
            if (p) {
                p->showConfigureDialog(this);
            } else {
                qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to find text plugin " << identifier;
            }
        } else if (groupName == toolPluginGroupName()) {
            if (const auto p = TextAutoGenerateTextToolPluginManager::self()->pluginFromIdentifier(identifier); p) {
                p->showConfigureDialog(this);
            } else {
                qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to find text plugin " << identifier;
            }

        } else {
            qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "plugin group name not supported " << groupName;
        }
    }
}

#include "moc_textautogeneratetextconfigurepluginswidget.cpp"
