/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selecttypecombobox.h"
#include <KLocalizedString>

using namespace TextAutoGenerateTextMcpProtocolWidgets;

SelectTypeComboBox::SelectTypeComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fill();
}

SelectTypeComboBox::~SelectTypeComboBox() = default;

void SelectTypeComboBox::addServerType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type)
{
    addItem(TextAutoGenerateTextMcpProtocolCore::McpServer::transportTypeI18n(type), QVariant::fromValue(type));
}

void SelectTypeComboBox::fill()
{
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse);
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio);
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType SelectTypeComboBox::type() const
{
    return currentData().value<TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType>();
}

void SelectTypeComboBox::setType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type)
{
    const int index = findData(QVariant::fromValue(type));
    if (index != -1) {
        setCurrentIndex(index);
    } else {
        setCurrentIndex(0);
    }
}

#include "moc_selecttypecombobox.cpp"
