/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "configurepluginswidget.h"
#include "configurepluginstreewidgetdelegate.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KMessageWidget>
#include <KTreeWidgetSearchLine>
#include <KTreeWidgetSearchLineWidget>
#include <QHeaderView>
#include <QToolButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAddonsWidgets;

ConfigurePluginsWidget::ConfigurePluginsWidget(QWidget *parent)
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

    mTreePluginWidget->setItemDelegate(new ConfigurePluginsTreeWidgetDelegate(this));
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

    connect(mTreePluginWidget, &QTreeWidget::itemChanged, this, &ConfigurePluginsWidget::slotItemChanged);

    mainLayout->addWidget(mMessageWidget);
    mainLayout->addWidget(mSearchLineEdit);
    mainLayout->addWidget(mTreePluginWidget);
}

ConfigurePluginsWidget::~ConfigurePluginsWidget() = default;

void ConfigurePluginsWidget::slotItemChanged([[maybe_unused]] QTreeWidgetItem *item, int column)
{
    if (mInitializeDone) {
        if (column == 0) {
            mMessageWidget->animatedShow();
        }
    }
}

void ConfigurePluginsWidget::save()
{
}

void ConfigurePluginsWidget::load()
{
    initialize();
    initializeDone();
}

void ConfigurePluginsWidget::defaults()
{
}

void ConfigurePluginsWidget::doLoadFromGlobalSettings()
{
}

void ConfigurePluginsWidget::doResetToDefaultsOther()
{
}

void ConfigurePluginsWidget::initialize()
{
}

void ConfigurePluginsWidget::initializeDone()
{
    mInitializeDone = true;
}

void ConfigurePluginsWidget::savePlugins(const QString &groupName, const QString &prefixSettingKey, const QList<PluginItem *> &listItems)
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

    TextAddonsWidgets::PluginUtil::savePluginSettings({}, groupName, prefixSettingKey, enabledPlugins, disabledPlugins);
}

void ConfigurePluginsWidget::fillTopItems(const QList<TextAddonsWidgets::PluginUtilData> &lst,
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
        const TextAddonsWidgets::PluginUtil::PluginsStateList pair = TextAddonsWidgets::PluginUtil::loadPluginSetting({}, groupName, prefixKey);
        for (const TextAddonsWidgets::PluginUtilData &data : lst) {
            auto subItem = new PluginItem(topLevel);
            subItem->setData(0, ConfigurePluginsWidget::PluginItemData::Description, data.mDescription);
            subItem->setText(0, data.mName);
            subItem->mIdentifier = data.mIdentifier;
            subItem->mEnableByDefault = data.mEnableByDefault;
            subItem->mHasConfigureSupport = data.mHasConfigureDialog;
            if (checkable) {
                const bool isPluginActivated =
                    TextAddonsWidgets::PluginUtil::isPluginActivated(pair.enabledPluginList, pair.disabledPluginList, data.mEnableByDefault, data.mIdentifier);
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
                connect(but, &QToolButton::triggered, this, &ConfigurePluginsWidget::slotConfigureButtonClicked);
            }
            itemsList.append(subItem);
        }
    }
}

void ConfigurePluginsWidget::slotConfigureButtonClicked(QAction *act)
{
    if (act) {
        const QStringList lst = act->data().toStringList();
        if (lst.count() == 2) {
            Q_EMIT configureClicked(lst.at(0), lst.at(1));
        }
    }
}

void ConfigurePluginsWidget::changeState(const QList<PluginItem *> &items)
{
    for (PluginItem *item : items) {
        item->setCheckState(0, item->mEnableByDefault ? Qt::Checked : Qt::Unchecked);
    }
}

void ConfigurePluginsWidget::resetToUserSettings(const QList<PluginItem *> &items)
{
    for (PluginItem *item : items) {
        item->setCheckState(0, item->mEnableFromUserSettings ? Qt::Checked : Qt::Unchecked);
    }
}

#include "moc_configurepluginswidget.cpp"
