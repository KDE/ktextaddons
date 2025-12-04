/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextclient.h"
#include <KLocalizedString>
#include <QDebug>
using namespace TextAutoGenerateText;
TextAutoGenerateTextClient::TextAutoGenerateTextClient(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextClient::~TextAutoGenerateTextClient() = default;

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
