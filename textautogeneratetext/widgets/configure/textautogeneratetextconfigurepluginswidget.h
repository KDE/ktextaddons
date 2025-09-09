/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QTreeWidgetItem>
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGeneratePluginUtils>
class KTreeWidgetSearchLineWidget;
class QTreeWidget;
class KMessageWidget;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextConfigurePluginsWidget : public QWidget
{
    Q_OBJECT
public:
    enum PluginItemData {
        Description = Qt::UserRole + 1,
    };
    explicit TextAutoGenerateTextConfigurePluginsWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextConfigurePluginsWidget() override;

    void save();
    void load();

Q_SIGNALS:
    void changed();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void initialize();
    TEXTAUTOGENERATETEXT_NO_EXPORT void initializeDone();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotItemChanged(QTreeWidgetItem *item, int column);

    class PluginItem : public QTreeWidgetItem
    {
    public:
        explicit PluginItem(QTreeWidgetItem *parent)
            : QTreeWidgetItem(parent)
        {
        }

        QString mIdentifier;
        bool mEnableByDefault = false;
        bool mHasConfigureSupport = false;
        bool mEnableFromUserSettings = false;
    };
    TEXTAUTOGENERATETEXT_NO_EXPORT void savePlugins(const QString &groupName, const QString &prefixSettingKey, const QList<PluginItem *> &listItems);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureClicked(QAction *act);

    KTreeWidgetSearchLineWidget *mSearchLineEdit = nullptr;
    QTreeWidget *const mTreePluginWidget;
    KMessageWidget *const mMessageWidget;
    bool mInitializeDone = false;
    TEXTAUTOGENERATETEXT_NO_EXPORT void fillTopItems(const QList<TextAutoGeneratePluginUtils::PluginUtilData> &lst,
                                                     const QString &topLevelItemName,
                                                     const QString &groupName,
                                                     const QString &prefixKey,
                                                     QList<PluginItem *> &itemsList,
                                                     const QString &configureGroupName,
                                                     bool checkable = true);
    QList<PluginItem *> mPluginTextItems;
};
}
