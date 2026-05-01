/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <KConfigGroup>
#include <QUrl>
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpServer
{
    Q_GADGET
public:
    enum class ServerType : int8_t {
        Unknown = 0,
        Sse,
        Stdio,
        StreamableHttp,
    };
    Q_ENUM(ServerType)

    McpServer();
    ~McpServer();

    void createUniqueIdentifier();

    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QByteArray identifier() const;
    void setIdentifier(const QByteArray &newIdentifier);

    void load(const KConfigGroup &config);
    void save(KConfigGroup &config) const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] ServerType serverType() const;
    void setServerType(ServerType newServerType);

    [[nodiscard]] QString command() const;
    void setCommand(const QString &newCommand);

    [[nodiscard]] QStringList arguments() const;
    void setArguments(const QStringList &newArguments);

    [[nodiscard]] QMap<QString, QString> environments() const;
    void setEnvironments(const QMap<QString, QString> &newEnvironments);

private:
    bool mEnabled = true;
    QUrl mServerUrl;
    QString mName;
    QByteArray mIdentifier;
    ServerType mServerType = ServerType::Unknown;
    QString mCommand;
    QStringList mArguments;
    QMap<QString, QString> mEnvironments;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpServer, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpServer &t);
