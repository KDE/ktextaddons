/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateTextMcpServer>
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateText::McpServerModel
 * \brief The McpServerModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/McpServerModel
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpServerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MCPServerRoles : uint16_t {
        Name = Qt::UserRole + 1,
        Enabled,
        Identifier,
    };
    /*!
     * Constructs a new McpServerModel object.
     * \param parent The parent QObject
     */
    explicit McpServerModel(QObject *parent = nullptr);
    /*!
     * Destroys the McpServerModel object.
     */
    ~McpServerModel() override;

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
     * Returns the list of mcp servers in the model.
     * \return The list of TextAutoGenerateTextMcpServer pointers
     */
    [[nodiscard]] QList<TextAutoGenerateTextMcpServer> mcpServers() const;
    /*!
     * Sets the list of mcp servers in the model.
     * \param newTextInstances The instances to set
     */
    void setMcpServers(const QList<TextAutoGenerateTextMcpServer> &newTextInstances);

    /*!
     * Adds an instance to the model.
     * \param instance The instance to add
     */
    void addMcpServer(const TextAutoGenerateTextMcpServer &instance);
    /*!
     * Returns whether the model is empty.
     * \return true if empty, false otherwise
     */
    [[nodiscard]] bool isEmpty() const;

    /*!
     * \brief removeMcpServer
     * \param id
     */
    void removeMcpServer(const QByteArray &id);

    /*!
     * \brief mpcServer
     * \param identifier
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextMcpServer mpcServer(const QByteArray &identifier) const;

private:
    QList<TextAutoGenerateTextMcpServer> mMcpServers;
};
}
