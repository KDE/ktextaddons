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

void SelectTypeComboBox::addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType type)
{
    addItem(TextAutoGenerateTextMcpProtocolCore::McpServer::transportTypeI18n(type), QVariant::fromValue(type));
}

void SelectTypeComboBox::fill()
{
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Sse);
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Stdio);
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::StreamableHttp);
}

TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType SelectTypeComboBox::type() const
{
    return currentData().value<TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType>();
}

void SelectTypeComboBox::setType(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType type)
{
    const int index = findData(QVariant::fromValue(type));
    if (index != -1) {
        setCurrentIndex(index);
    } else {
        setCurrentIndex(0);
    }
}

#include "moc_selecttypecombobox.cpp"
