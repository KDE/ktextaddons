/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QMap>
#include <QObject>
#include <QString>
#include <QUrl>
class QDebug;
class KConfigGroup;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSettings
{
public:
    McpProtocolSettings();
    ~McpProtocolSettings();

    [[nodiscard]] QString command() const;
    void setCommand(const QString &newCommand);

    [[nodiscard]] QString arguments() const;
    void setArguments(const QString &newArguments);

    [[nodiscard]] QMap<QString, QString> environments() const;
    void setEnvironments(const QMap<QString, QString> &newEnvironments);

    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

    void load(const KConfigGroup &config);
    void save(KConfigGroup &config) const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QMap<QString, QString> headers() const;
    void setHeaders(const QMap<QString, QString> &newHeaders);

private:
    QUrl mServerUrl;
    QString mCommand;
    QString mArguments;
    QMap<QString, QString> mEnvironments;
    QMap<QString, QString> mHeaders;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &t);
