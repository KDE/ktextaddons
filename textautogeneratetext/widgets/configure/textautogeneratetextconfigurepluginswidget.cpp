/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfigurepluginswidget.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "textautogeneratetextconfigurepluginstreewidgetdelegate.h"
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
    : QWidget{parent}
    , mTreePluginWidget(new QTreeWidget(this))
    , mMessageWidget(new KMessageWidget(i18n("Restart is necessary for applying the changes."), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mMessageWidget->setObjectName(u"mMessageWidget"_s);
    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setVisible(false);
    mMessageWidget->setPosition(KMessageWidget::Header);

    mTreePluginWidget->setItemDelegate(new TextAutoGenerateTextConfigurePluginsTreeWidgetDelegate(this));
    mTreePluginWidget->setObjectName(u"mTreePluginWidget"_s);
    mTreePluginWidget->setSortingEnabled(true);
    mTreePluginWidget->sortItems(0, Qt::AscendingOrder);
    mTreePluginWidget->setHeaderHidden(true);
    mTreePluginWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    mTreePluginWidget->setColumnCount(2);

    mTreePluginWidget->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    mTreePluginWidget->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    mTreePluginWidget->header()->setStretchLastSection(false);

    mSearchLineEdit = new KTreeWidgetSearchLineWidget(this, mTreePluginWidget);
    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mSearchLineEdit->searchLine()->setProperty("_breeze_borders_sides", QVariant::fromValue(QFlags{Qt::BottomEdge}));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit->searchLine());

    connect(mTreePluginWidget, &QTreeWidget::itemChanged, this, &TextAutoGenerateTextConfigurePluginsWidget::slotItemChanged);

    mainLayout->addWidget(mMessageWidget);
    mainLayout->addWidget(mSearchLineEdit);
    mainLayout->addWidget(mTreePluginWidget);
}

TextAutoGenerateTextConfigurePluginsWidget::~TextAutoGenerateTextConfigurePluginsWidget() = default;

void TextAutoGenerateTextConfigurePluginsWidget::slotItemChanged([[maybe_unused]] QTreeWidgetItem *item, int column)
{
    if (mInitializeDone) {
        if (column == 0) {
            mMessageWidget->animatedShow();
        }
    }
}

void TextAutoGenerateTextConfigurePluginsWidget::save()
{
    savePlugins(TextAutoGeneratePluginTextManager::self()->configGroupName(),
                TextAutoGeneratePluginTextManager::self()->configPrefixSettingKey(),
                mPluginTextItems);
}

void TextAutoGenerateTextConfigurePluginsWidget::load()
{
    initialize();
    initializeDone();
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
                 mPluginTextItems,
                 toolPluginGroupName());

    mTreePluginWidget->expandAll();
}

void TextAutoGenerateTextConfigurePluginsWidget::initializeDone()
{
    mInitializeDone = true;
}

void TextAutoGenerateTextConfigurePluginsWidget::savePlugins(const QString &groupName, const QString &prefixSettingKey, const QList<PluginItem *> &listItems)
{
    if (listItems.isEmpty()) {
        return;
    }
    QStringList enabledPlugins;
    QStringList disabledPlugins;
    for (const PluginItem *item : listItems) {
        if (item->checkState(0) == Qt::Checked) {
            enabledPlugins << item->mIdentifier;
        } else {
            disabledPlugins << item->mIdentifier;
        }
    }

    TextAutoGeneratePluginUtils::savePluginSettings(groupName, prefixSettingKey, enabledPlugins, disabledPlugins);
}

void TextAutoGenerateTextConfigurePluginsWidget::fillTopItems(const QList<TextAutoGeneratePluginUtils::PluginUtilData> &lst,
                                                              const QString &topLevelItemName,
                                                              const QString &groupName,
                                                              const QString &prefixKey,
                                                              QList<PluginItem *> &itemsList,
                                                              const QString &configureGroupName,
                                                              bool checkable)
{
    itemsList.clear();
    if (!lst.isEmpty()) {
        auto topLevel = new QTreeWidgetItem(mTreePluginWidget, {topLevelItemName});
        topLevel->setFlags(topLevel->flags() & ~Qt::ItemIsSelectable);
        const QPair<QStringList, QStringList> pair = TextAutoGeneratePluginUtils::loadPluginSetting(groupName, prefixKey);
        for (const TextAutoGeneratePluginUtils::PluginUtilData &data : lst) {
            auto subItem = new PluginItem(topLevel);
            subItem->setData(0, TextAutoGenerateTextConfigurePluginsWidget::PluginItemData::Description, data.mDescription);
            subItem->setText(0, data.mName);
            subItem->mIdentifier = data.mIdentifier;
            subItem->mEnableByDefault = data.mEnableByDefault;
            subItem->mHasConfigureSupport = data.mHasConfigureDialog;
            if (checkable) {
                const bool isPluginActivated = TextAutoGeneratePluginUtils::isPluginActivated(pair.first, pair.second, data.mEnableByDefault, data.mIdentifier);
                subItem->mEnableFromUserSettings = isPluginActivated;
                subItem->setCheckState(0, isPluginActivated ? Qt::Checked : Qt::Unchecked);
            }
            if (data.mHasConfigureDialog) {
                auto but = new QToolButton(mTreePluginWidget);
                auto act = new QAction(but);
                const QStringList actData{configureGroupName, data.mIdentifier};
                act->setData(actData);
                but->setDefaultAction(act);
                but->setIcon(QIcon::fromTheme(u"configure"_s));
                but->setText(i18n("..."));
                but->setFixedWidth(28);
                but->setToolTip(i18nc("@info:tooltip", "Configure"));
                but->setAutoFillBackground(true);
                but->setEnabled(subItem->mHasConfigureSupport);
                mTreePluginWidget->setItemWidget(subItem, 1, but);
                connect(but, &QToolButton::triggered, this, &TextAutoGenerateTextConfigurePluginsWidget::slotConfigureClicked);
            }
            itemsList.append(subItem);
        }
    }
}

void TextAutoGenerateTextConfigurePluginsWidget::slotConfigureClicked(QAction *act)
{
    if (act) {
        const QStringList lst = act->data().toStringList();
        if (lst.count() == 2) {
            const QString &groupName = lst.at(0);
            const QString &identifier = lst.at(1);
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
    }
}

#include "moc_textautogeneratetextconfigurepluginswidget.cpp"
