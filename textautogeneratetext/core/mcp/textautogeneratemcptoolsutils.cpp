/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolsutils.h"
#include <KConfigGroup>
#include <KSharedConfig>
using namespace Qt::Literals::StringLiterals;
bool TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::isServerAlwaysAllowed(const QString &serverConfigFileName, const QByteArray &serverIdentifier)
{
    const KConfigGroup group(KSharedConfig::openConfig(serverConfigFileName), u"ToolConfirmation"_s);
    return group.readEntry("AlwaysAllowedServers", QStringList()).contains(QString::fromLatin1(serverIdentifier));
}

void TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::setServerAlwaysAllowed(const QString &serverConfigFileName,
                                                                                 const QByteArray &serverIdentifier,
                                                                                 bool allowed)
{
    KConfigGroup group(KSharedConfig::openConfig(serverConfigFileName), u"ToolConfirmation"_s);
    QStringList servers = group.readEntry("AlwaysAllowedServers", QStringList());
    const QString identifier = QString::fromLatin1(serverIdentifier);
    servers.removeAll(identifier);
    if (allowed) {
        servers.append(identifier);
    }
    group.writeEntry("AlwaysAllowedServers", servers);
    group.sync();
}
