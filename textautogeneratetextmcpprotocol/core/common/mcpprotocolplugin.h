/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolPluginInterface;
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolPlugin : public QObject
{
    Q_OBJECT
public:
    enum class PluginType : uint8_t {
        Unknown = 0,
        Server,
        Client,
    };
    Q_ENUM(PluginType)

    enum class TransportType : uint8_t {
        Unknown = 0,
        Sse,
        Stdio,
        StreamableHttp,
    };
    Q_ENUM(TransportType)

    /*!
     */
    explicit McpProtocolPlugin(QObject *parent = nullptr);
    /*!
     */
    ~McpProtocolPlugin() override;

    /*!
     */
    [[nodiscard]] PluginType pluginType() const;

    /*!
     */
    [[nodiscard]] virtual McpProtocolPluginInterface *createInterface(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type,
                                                                      QObject *parent) = 0;

protected:
    PluginType mPluginType = PluginType::Unknown;
};
}
