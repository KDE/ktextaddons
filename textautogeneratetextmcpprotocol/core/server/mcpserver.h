/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QMap>
#include <QObject>
#include <QUrl>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPlugin>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
class QDebug;
class KConfigGroup;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpServer
{
    Q_GADGET
public:
    McpServer();
    ~McpServer();

    void createUniqueIdentifier();

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QByteArray identifier() const;
    void setIdentifier(const QByteArray &newIdentifier);

    void load(const KConfigGroup &config);
    void save(KConfigGroup &config) const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType transportType() const;
    void setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType newServerType);

    [[nodiscard]] static QString convertTransportTypeToString(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type);
    [[nodiscard]] static TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType convertTransportTypeFromString(const QString &str);
    [[nodiscard]] static QString transportTypeI18n(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type);

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings() const;
    void setSettings(const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &newSettings);

private:
    bool mEnabled = true;
    QString mName;
    QByteArray mIdentifier;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType mTransportType =
        TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings mSettings;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpServer, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpServer &t);
