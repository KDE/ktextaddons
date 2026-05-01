/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServerModel;
/*!
 * \class TextAutoGenerateText::McpServerManager
 * \brief The McpServerManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/McpServerManager
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
     * \brief textAutoGenerateTextMcpServerModel
     * \return
     */
    [[nodiscard]] McpServerModel *textAutoGenerateTextMcpServerModel() const;

    /*!
     * \brief loadServers
     */
    void loadServers();

    /*!
     * \brief saveServers
     */
    void saveServers();

private:
    McpServerModel *const mTextAutoGenerateTextMcpServerModel;
};
}
