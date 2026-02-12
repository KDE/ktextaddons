/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateTextInstance>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstanceModel
 * \brief The TextAutoGenerateTextInstanceModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstanceModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstanceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum InstanceRoles : uint16_t {
        Name = Qt::UserRole + 1,
        PluginName,
        PluginIdentifier,
        Uuid,
        Plugin,
        Enabled,
        IsDefault,
        TranslatedPluginName,
    };
    /*!
     * Constructs a new TextAutoGenerateTextInstanceModel object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateTextInstanceModel(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateTextInstanceModel object.
     */
    ~TextAutoGenerateTextInstanceModel() override;

    /*!
     * Returns the number of rows in the model.
     * \return The row count
     */
    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    /*!
     * Returns the data at the given index for the specified role.
     * \param index The model index
     * \param role The data role
     * \return The data value
     */
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    /*!
     * Sets the data at the given index for the specified role.
     * \param index The model index
     * \param value The value to set
     * \param role The data role
     * \return true if successful, false otherwise
     */
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*!
     * Returns the flags for the given index.
     * \param index The model index
     * \return The item flags
     */
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    /*!
     * Returns the list of text instances in the model.
     * \return The list of TextAutoGenerateTextInstance pointers
     */
    [[nodiscard]] QList<TextAutoGenerateTextInstance *> textInstances() const;
    /*!
     * Sets the list of text instances in the model.
     * \param newTextInstances The instances to set
     */
    void setTextInstances(const QList<TextAutoGenerateTextInstance *> &newTextInstances);

    /*!
     * Adds an instance to the model.
     * \param instance The instance to add
     */
    void addInstance(TextAutoGenerateTextInstance *instance);

    /*!
     * Removes an instance from the model by UUID.
     * \param uuid The UUID of the instance to remove
     * \return The plugin from the removed instance
     */
    [[nodiscard]] TextAutoGenerateTextPlugin *removeInstance(const QByteArray &uuid);

    /*!
     * Gets the plugin for editing an instance by UUID.
     * \param uuid The UUID of the instance to edit
     * \return The plugin from the instance
     */
    [[nodiscard]] TextAutoGenerateTextPlugin *editInstance(const QByteArray &uuid);

    /*!
     * Returns whether the model is empty.
     * \return true if empty, false otherwise
     */
    [[nodiscard]] bool isEmpty() const;

    /*!
     * Returns the UUID of the current instance.
     * \return The current instance UUID
     */
    [[nodiscard]] QByteArray currentInstance() const;
    /*!
     * Sets the current instance by UUID.
     * \param newCurrentinstance The UUID to set as current
     */
    void setCurrentInstance(const QByteArray &newCurrentinstance);

    /*!
     * Returns the plugin of the current instance.
     * \return The plugin pointer or nullptr
     */
    [[nodiscard]] TextAutoGenerateTextPlugin *currentPlugin() const;

    /*!
     * Returns a list of display names for all instances.
     * \return List of instance display names
     */
    [[nodiscard]] QStringList instanceDisplayNames() const;

private:
    QList<TextAutoGenerateTextInstance *> mTextInstances;
    QByteArray mCurrentinstance;
};
}
