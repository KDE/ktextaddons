/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralclient.h"
#include "mistralconfiguredialog.h"
#include "mistralmanager.h"
#include "mistralplugin.h"

#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
MistralClient::MistralClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}
    , mManager(new MistralManager(parent))
{
}

MistralClient::~MistralClient() = default;

QString MistralClient::name() const
{
    return "mistral"_L1;
}

QString MistralClient::translatedName() const
{
    return i18n("Mistral AI");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *MistralClient::createTextAutoGeneratePlugin()
{
    return new MistralPlugin(mManager, this);
}

TextAutoGenerateText::TextAutoGenerateTextClient::EngineType MistralClient::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextClient::EngineType::Network;
}

bool MistralClient::hasConfigurationDialog() const
{
    return true;
}

bool MistralClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO use QPointer here ???
    MistralConfigureDialog d(parentWidget);
    bool b = d.exec();
    if (b) {
        // TODO save
    }
    return b;
}

QString MistralClient::webSite() const
{
    return QStringLiteral("https://chat.mistral.ai/");
}

QString MistralClient::modelName() const
{
    // No model here
    return {};
}

#include "moc_mistralclient.cpp"
