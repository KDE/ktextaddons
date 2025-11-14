/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfigurepluginswidget.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/plugintext/textautogenerateplugintextmanager.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KMessageWidget>
#include <KTreeWidgetSearchLine>
#include <KTreeWidgetSearchLineWidget>
#include <QHeaderView>
#include <QToolButton>
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
    fillTopItems(TextAutoGeneratePluginTextManager::self()->pluginDataList(),
                 i18n("Text Plugins"),
                 TextAutoGeneratePluginTextManager::self()->configGroupName(),
                 TextAutoGeneratePluginTextManager::self()->configPrefixSettingKey(),
                 mPluginTextItems,
                 textPluginGroupName());

    fillTopItems(TextAutoGenerateTextToolPluginManager::self()->pluginDataList(),
                 i18n("Tools Plugins"),
                 TextAutoGenerateTextToolPluginManager::self()->configGroupName(),
                 TextAutoGenerateTextToolPluginManager::self()->configPrefixSettingKey(),
                 mPluginToolsItems,
                 toolPluginGroupName());

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
            const auto p = TextAutoGenerateTextToolPluginManager::self()->pluginFromIdentifier(identifier);
            if (p) {
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
