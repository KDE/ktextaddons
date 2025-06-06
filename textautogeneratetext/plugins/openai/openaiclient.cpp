/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openaiclient.h"
#include "openaiconfiguredialog.h"
#include "openaiplugin.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OpenAIClient::OpenAIClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}
{
}

OpenAIClient::~OpenAIClient() = default;

QString OpenAIClient::name() const
{
    return OpenAIPlugin::name();
}

QString OpenAIClient::translatedName() const
{
    return i18n("OpenAI");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *OpenAIClient::createTextAutoGeneratePlugin()
{
    return new OpenAIPlugin(this);
}

TextAutoGenerateText::TextAutoGenerateTextClient::EngineType OpenAIClient::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextClient::EngineType::Network;
}

bool OpenAIClient::hasConfigurationDialog() const
{
    return true;
}

bool OpenAIClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO use QPointer here ???
    OpenAIConfigureDialog d(parentWidget);
    return d.exec();
}

QString OpenAIClient::webSite() const
{
    return QStringLiteral("https://openai.com/");
}

QString OpenAIClient::modelName() const
{
    // No model here
    return {};
}

#include "moc_openaiclient.cpp"
