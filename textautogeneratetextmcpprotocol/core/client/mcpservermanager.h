/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QList>
#include <QMap>
#include <QObject>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServerModel;
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpServerManager
 * \brief The McpServerManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpServerManager
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpServerManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief McpServerManager
     * \param parent
     */
    explicit McpServerManager(QObject *parent = nullptr);
    /*!
     */
    ~McpServerManager() override;

    /*!
     * \brief mcpServerModel
     * \return
     */
    [[nodiscard]] McpServerModel *mcpServerModel() const;

    /*!
     * \brief loadServers
     */
    void loadServers();

    /*!
     * \brief saveServers
     */
    void saveServers();

    /*!
     * \brief serverConfigFileName
     * \return
     */
    [[nodiscard]] virtual QString serverConfigFileName() const;

Q_SIGNALS:
    /*!
     * \brief serverLoaded
     */
    void serverLoaded();

private:
    // Invalid servers (unknown transport…) are not shown but must be kept in config
    QList<QMap<QString, QString>> mInvalidServerEntries;
    McpServerModel *const mMcpServerModel;
};
}
