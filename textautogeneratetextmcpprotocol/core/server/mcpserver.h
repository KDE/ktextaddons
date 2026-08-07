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
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpServer
 * \brief The McpServer class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpServer
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpServer
{
    Q_GADGET
public:
    /*!
     * \brief McpServer
     */
    McpServer();
    /*!
     * \brief ~McpServer
     */
    ~McpServer();

    /*!
     * \brief createUniqueIdentifier
     */
    void createUniqueIdentifier();

    /*!
     * \brief enabled
     * \return
     */
    [[nodiscard]] bool enabled() const;
    /*!
     * \brief setEnabled
     * \param newEnabled
     */
    void setEnabled(bool newEnabled);
    /*!
     * \brief name
     * \return
     */
    [[nodiscard]] QString name() const;
    /*!
     * \brief setName
     * \param newName
     */
    void setName(const QString &newName);

    /*!
     * \brief identifier
     * \return
     */
    [[nodiscard]] QByteArray identifier() const;
    /*!
     * \brief setIdentifier
     * \param newIdentifier
     */
    void setIdentifier(const QByteArray &newIdentifier);

    /*!
     * \brief load
     * \param config
     */
    void load(const KConfigGroup &config);
    /*!
     * \brief save
     * \param config
     */
    void save(KConfigGroup &config) const;

    /*!
     * \brief isValid
     * \return
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * \brief transportType
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType transportType() const;
    /*!
     * \brief setTransportType
     * \param newServerType
     */
    void setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType newServerType);

    /*!
     * \brief convertTransportTypeToString
     * \param type
     * \return
     */
    [[nodiscard]] static QString convertTransportTypeToString(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type);
    /*!
     * \brief convertTransportTypeFromString
     * \param str
     * \return
     */
    [[nodiscard]] static TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType convertTransportTypeFromString(const QString &str);
    /*!
     * \brief transportTypeI18n
     * \param type
     * \return
     */
    [[nodiscard]] static QString transportTypeI18n(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type);

    /*!
     * \brief settings
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings() const;
    /*!
     * \brief setSettings
     * \param newSettings
     */
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
