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
     * \brief The Icon class
     */
    struct Icon {
        QString url;
        QString mimetype;
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

    /*!
     * \brief description
     * \return
     */
    [[nodiscard]] QString description() const;
    /*!
     * \brief setDescription
     * \param newDescription
     */
    void setDescription(const QString &newDescription);

    /*!
     * \brief version
     * \return
     */
    [[nodiscard]] QString version() const;
    /*!
     * \brief setVersion
     * \param newVersion
     */
    void setVersion(const QString &newVersion);

    /*!
     * \brief repositoryUrl
     * \return
     */
    [[nodiscard]] QString repositoryUrl() const;
    /*!
     * \brief setRepositoryUrl
     * \param newRepositoryUrl
     */
    void setRepositoryUrl(const QString &newRepositoryUrl);

    /*!
     * \brief websiteUrl
     * \return
     */
    [[nodiscard]] QString websiteUrl() const;
    /*!
     * \brief setWebsiteUrl
     * \param newWebsiteUrl
     */
    void setWebsiteUrl(const QString &newWebsiteUrl);

    /*!
     * \brief packages
     * \return
     */
    [[nodiscard]] QList<Package> packages() const;
    /*!
     * \brief setPackages
     * \param newPackages
     */
    void setPackages(const QList<Package> &newPackages);

    /*!
     * \brief remotes
     * \return
     */
    [[nodiscard]] QList<Remote> remotes() const;
    /*!
     * \brief setRemotes
     * \param newRemotes
     */
    void setRemotes(const QList<Remote> &newRemotes);

    /*!
     * \brief icons
     * \return
     */
    [[nodiscard]] QList<Icon> icons() const;
    /*!
     * \brief setIcons
     * \param newIcons
     */
    void setIcons(const QList<Icon> &newIcons);

private:
    QList<Icon> mIcons;
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
