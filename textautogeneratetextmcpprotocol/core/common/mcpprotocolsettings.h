/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QMap>
#include <QStringList>
#include <QUrl>
class QDebug;
class KConfigGroup;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSettings
{
public:
    /*!
     * \brief McpProtocolSettings
     */
    McpProtocolSettings();
    /*!
     * \brief operator ==
     * \param other
     * \return
     */
    [[nodiscard]] bool operator==(const McpProtocolSettings &other) const;

    /*!
     * \brief command
     * \return
     */
    [[nodiscard]] QString command() const;
    /*!
     * \brief setCommand
     * \param newCommand
     */
    void setCommand(const QString &newCommand);

    /*!
     * \brief arguments
     * \return
     */
    [[nodiscard]] QString arguments() const;
    /*!
     * \brief setArguments
     * \param newArguments
     */
    void setArguments(const QString &newArguments);

    /*!
     * \brief environments
     * \return
     */
    [[nodiscard]] QMap<QString, QString> environments() const;
    /*!
     * \brief setEnvironments
     * \param newEnvironments
     */
    void setEnvironments(const QMap<QString, QString> &newEnvironments);

    /*!
     * \brief serverUrl
     * \return
     */
    [[nodiscard]] QUrl serverUrl() const;
    /*!
     * \brief setServerUrl
     * \param newServerUrl
     */
    void setServerUrl(const QUrl &newServerUrl);

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
     * Valid http or https url (sse and streamable http transports)
     */
    [[nodiscard]] bool hasValidServerUrl() const;
    /*!
     * Command is defined (stdio transport)
     */
    [[nodiscard]] bool hasValidCommand() const;

    /*!
     * \brief headers
     * \return
     */
    [[nodiscard]] QStringList headers() const;
    /*!
     * \brief setHeaders
     * \param newHeaders
     */
    void setHeaders(const QStringList &newHeaders);

    /*!
     * Local directories that server is allowed to access (MCP "roots").
     */
    [[nodiscard]] QStringList roots() const;
    /*!
     * \brief setRoots
     * \param newRoots
     */
    void setRoots(const QStringList &newRoots);

    /*!
     * \brief authToken
     * \return
     */
    [[nodiscard]] QByteArray authToken() const;
    /*!
     * \brief setAuthToken
     * \param newAuthToken
     */
    void setAuthToken(const QByteArray &newAuthToken);

private:
    QUrl mServerUrl;
    QString mCommand;
    QString mArguments;
    QMap<QString, QString> mEnvironments;
    QStringList mHeaders;
    QStringList mRoots;
    QByteArray mAuthToken;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &t);
