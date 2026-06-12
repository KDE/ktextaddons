/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "llamacppclient.h"
#include "llamacppplugin.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
LLamaCppClient::LLamaCppClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}
{
}

LLamaCppClient::~LLamaCppClient() = default;

QString LLamaCppClient::name() const
{
    return "llamacpp"_L1;
}

QString LLamaCppClient::translatedName() const
{
    return i18n("LLamaCpp");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *LLamaCppClient::createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                               TextAutoGenerateText::TextAutoGenerateTextInstance *instance)
{
    return new LLamaCppPlugin(manager, instance, this);
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> LLamaCppClient::supportedServers() const
{
    const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer info{
        .localizedName = QStringLiteral("%1 (%2)").arg(
            translatedName(),
            TextAutoGenerateText::TextAutoGenerateTextPlugin::convertEngineType(TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network)),
        .identifier = name(),
        .pluginName = name(),
    };
    return {info};
}
#include "moc_llamacppclient.cpp"
