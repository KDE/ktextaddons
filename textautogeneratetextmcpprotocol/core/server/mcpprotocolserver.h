/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPlugin>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServer
 * \brief The McpProtocolServer class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServer
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServer : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief McpProtocolServer
     * \param protocolType
     * \param parent
     */
    explicit McpProtocolServer(McpProtocolPlugin::TransportType protocolType, QObject *parent = nullptr);
    /*!
     * \brief ~McpProtocolServer
     */
    ~McpProtocolServer() override;

    /*!
     * \brief protocolType
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType protocolType() const;
    /*!
     * \brief setSettings
     * \param settings
     */
    void setSettings(const McpProtocolSettings &settings);

    /*!
     * \brief start
     */
    void start();

    /*!
     * \brief canStart
     * \return
     */
    [[nodiscard]] bool canStart() const;

Q_SIGNALS:
    /*!
     * \brief started
     */
    void started();
    /*!
     * \brief received
     * \param obj
     */
    void received(const QJsonObject &obj);
    /*!
     * \brief error
     * \param str
     */
    void error(const QString &str);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void loadPlugin();
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType mProtocolType;
    McpProtocolPlugin *mPlugin = nullptr;
    McpProtocolPluginInterface *mPluginInterface = nullptr;
    McpProtocolSettings mProtocolSettings;
};
}
