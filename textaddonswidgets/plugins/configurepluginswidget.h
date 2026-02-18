/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class TextAddonsWidgets::ConfigurePluginsWidget
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/ConfigurePluginsWidget
 *
 * \brief The ConfigurePluginsWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT ConfigurePluginsWidget : public QWidget
{
    Q_OBJECT
public:
    enum PluginItemData {
        Description = Qt::UserRole + 1,
    };
    /*!
     * \brief Constructor for ConfigurePluginsWidget
     * \param parent The parent widget
     */
    explicit ConfigurePluginsWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for ConfigurePluginsWidget
     */
    ~ConfigurePluginsWidget() override;

    /*!
     * \brief Saves the current plugin configuration
     */
    virtual void save();
    /*!
     * \brief Loads the plugin configuration
     */
    virtual void load();
    /*!
     * \brief Resets to default plugin settings
     */
    virtual void defaults();
    /*!
     * \brief Loads configuration from global settings
     */
    virtual void doLoadFromGlobalSettings();
    /*!
     * \brief Resets to default settings other than enabled state
     */
    virtual void doResetToDefaultsOther();
    /*!
     * \brief Initializes the configure plugins widget
     */
    virtual void initialize();

Q_SIGNALS:
    /*!
     * \brief Emitted when the plugin configuration has changed
     */
    void changed();
    /*!
     * \brief Emitted when the configure button is clicked for a plugin
     * \param configureGroupName The configuration group name
     * \param identifier The plugin identifier
     */
    void configureClicked(const QString &configureGroupName, const QString &identifier);

protected:
    /*!
     * \brief The tree widget for displaying plugins
     */
    QTreeWidget *const mTreePluginWidget;
    /*!
     * \brief Called when initialization is complete
     */
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
