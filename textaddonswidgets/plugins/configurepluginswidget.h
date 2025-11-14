/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <QList>
#include <QTreeWidgetItem>
#include <QWidget>
#include <TextAddonsWidgets/PluginUtil>
class KTreeWidgetSearchLineWidget;
class QTreeWidget;
class KMessageWidget;
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT ConfigurePluginsWidget : public QWidget
{
    Q_OBJECT
public:
    enum PluginItemData {
        Description = Qt::UserRole + 1,
    };
    explicit ConfigurePluginsWidget(QWidget *parent = nullptr);
    ~ConfigurePluginsWidget() override;

    virtual void save();
    virtual void load();
    virtual void defaults();
    virtual void doLoadFromGlobalSettings();
    virtual void doResetToDefaultsOther();
    virtual void initialize();

Q_SIGNALS:
    void changed();
    void configureClicked(const QString &configureGroupName, const QString &identifier);

protected:
    QTreeWidget *const mTreePluginWidget;
    void initializeDone();

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
    void fillTopItems(const QList<TextAddonsWidgets::PluginUtilData> &lst,
                      const QString &topLevelItemName,
                      const QString &groupName,
                      const QString &prefixKey,
                      QList<PluginItem *> &itemsList,
                      const QString &configureGroupName,
                      bool checkable = true,
                      const QString &fileName = {});
    void resetToUserSettings(const QList<PluginItem *> &items);
    void changeState(const QList<PluginItem *> &items);
    void savePlugins(const QString &groupName, const QString &prefixSettingKey, const QList<PluginItem *> &listItems, const QString &configName = {});

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotItemChanged(QTreeWidgetItem *item, int column);

    TEXTADDONSWIDGETS_NO_EXPORT void slotConfigureButtonClicked(QAction *act);

    KTreeWidgetSearchLineWidget *mSearchLineEdit = nullptr;
    KMessageWidget *const mMessageWidget;
    bool mInitializeDone = false;
};
}
