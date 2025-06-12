/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextclient.h"
#include <KLocalizedString>
using namespace TextAutoGenerateText;
TextAutoGenerateTextClient::TextAutoGenerateTextClient(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextClient::~TextAutoGenerateTextClient() = default;

bool TextAutoGenerateTextClient::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget);
    // Nothing by default
    return false;
}

QString TextAutoGenerateTextClient::convertEngineType(TextAutoGenerateText::TextAutoGenerateTextClient::EngineType type)
{
    switch (type) {
    case TextAutoGenerateText::TextAutoGenerateTextClient::EngineType::Local:
        return i18n("Local");
    case TextAutoGenerateText::TextAutoGenerateTextClient::EngineType::Network:
        return i18n("Network");
    }
    Q_UNREACHABLE();
    return {};
}

bool TextAutoGenerateTextClient::SupportedServer::isValid() const
{
    return !localizedName.isEmpty() && !identifier.isEmpty() && !pluginName.isEmpty();
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer &t)
{
    d.space() << "localizedName:" << t.localizedName;
    d.space() << "identifier:" << t.identifier;
    d.space() << "pluginName:" << t.pluginName;
    return d;
}
#include "moc_textautogeneratetextclient.cpp"
