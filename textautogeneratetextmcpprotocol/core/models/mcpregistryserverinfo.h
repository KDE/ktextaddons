/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QDebug>
#include <QList>
#include <QString>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo
 * \brief The McpRegistryServerInfo class describes a server published in the official MCP registry
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateTextMcpProtocolCore
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpRegistryServerInfo
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpRegistryServerInfo
{
public:
    /*!
     * \brief Environment variable used by a package
     */
    struct EnvironmentVariable {
        QString name;
        QString description;
        bool isRequired = false;
        bool isSecret = false;
    };
    /*!
     * \brief Package (npm, pypi, oci, …) which allows to run the server locally
     */
    struct Package {
        QString registryType;
        QString identifier;
        QString version;
        QString runtimeHint;
        QString transportType;
        QList<EnvironmentVariable> environmentVariables;
    };
    /*!
     * \brief Remote endpoint of the server
     */
    struct Remote {
        QString type;
        QString url;
    };

    /*!
     * Constructs an empty McpRegistryServerInfo object.
     */
    McpRegistryServerInfo();
    /*!
     * Destroys the McpRegistryServerInfo object.
     */
    ~McpRegistryServerInfo();

    /*!
     * Creates a McpRegistryServerInfo from the "server" object of a registry answer.
     * \param obj The json object
     * \return The server info
     */
    [[nodiscard]] static McpRegistryServerInfo fromJson(const QJsonObject &obj);
    /*!
     * Parses the answer of the registry "servers" endpoint.
     * \param obj The json answer
     * \param nextCursor Set to the cursor of the next page, empty when there is no more page
     * \return The list of valid servers
     */
    [[nodiscard]] static QList<McpRegistryServerInfo> parseServerList(const QJsonObject &obj, QString &nextCursor);

    /*!
     * Returns true if the server has a name.
     */
    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QString title() const;
    void setTitle(const QString &newTitle);

    /*!
     * Returns the title if defined, otherwise the name.
     */
    [[nodiscard]] QString displayName() const;

    [[nodiscard]] QString description() const;
    void setDescription(const QString &newDescription);

    [[nodiscard]] QString version() const;
    void setVersion(const QString &newVersion);

    [[nodiscard]] QString repositoryUrl() const;
    void setRepositoryUrl(const QString &newRepositoryUrl);

    [[nodiscard]] QString websiteUrl() const;
    void setWebsiteUrl(const QString &newWebsiteUrl);

    [[nodiscard]] QList<Package> packages() const;
    void setPackages(const QList<Package> &newPackages);

    [[nodiscard]] QList<Remote> remotes() const;
    void setRemotes(const QList<Remote> &newRemotes);

private:
    QList<Package> mPackages;
    QList<Remote> mRemotes;
    QString mName;
    QString mTitle;
    QString mDescription;
    QString mVersion;
    QString mRepositoryUrl;
    QString mWebsiteUrl;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &t);
