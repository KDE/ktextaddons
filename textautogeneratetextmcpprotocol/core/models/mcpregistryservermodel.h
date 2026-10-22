/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerInfo>
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpRegistryServerModel
 * \brief The McpRegistryServerModel class lists servers from the official MCP registry
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateTextMcpProtocolCore
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpRegistryServerModel
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpRegistryServerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum McpRegistryServerRoles : uint16_t {
        Name = Qt::UserRole + 1,
        Description,
        Version,
    };
    Q_ENUM(McpRegistryServerRoles)

    /*!
     * Constructs a new McpRegistryServerModel object.
     * \param parent The parent QObject
     */
    explicit McpRegistryServerModel(QObject *parent = nullptr);
    /*!
     * Destroys the McpRegistryServerModel object.
     */
    ~McpRegistryServerModel() override;

    /*!
     * Returns the number of rows in the model.
     */
    [[nodiscard]] int rowCount(const QModelIndex &parent = {}) const override;
    /*!
     * Returns the data at the given index for the specified role.
     * \param index The model index
     * \param role The data role
     */
    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /*!
     * Replaces the servers of the model.
     * \param servers The servers to set
     */
    void setServers(const QList<McpRegistryServerInfo> &servers);
    /*!
     * Appends servers (next page) to the model.
     * \param servers The servers to append
     */
    void appendServers(const QList<McpRegistryServerInfo> &servers);
    /*!
     * Removes all servers from the model.
     */
    void clear();

    /*!
     * Returns the server info at \a row, or an invalid info if \a row is out of range.
     */
    [[nodiscard]] McpRegistryServerInfo serverInfo(int row) const;

private:
    QList<McpRegistryServerInfo> mServers;
};
}
