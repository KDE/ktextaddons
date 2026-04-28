/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudioclient.h"
#include "lmstudioplugin.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
LMStudioClient::LMStudioClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}
{
}

LMStudioClient::~LMStudioClient() = default;

QString LMStudioClient::name() const
{
    return "LMStudio"_L1;
}

QString LMStudioClient::translatedName() const
{
    return i18n("LMStudio");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *LMStudioClient::createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                               TextAutoGenerateText::TextAutoGenerateTextInstance *instance)
{
    return new LMStudioPlugin(manager, instance, this);
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> LMStudioClient::supportedServers() const
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
#include "moc_lmstudioclient.cpp"
