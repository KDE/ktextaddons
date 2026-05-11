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

void SelectTypeComboBox::addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType type)
{
    addItem(TextAutoGenerateTextMcpProtocolCore::McpServer::serverTypeI18n(type), QVariant::fromValue(type));
}

void SelectTypeComboBox::fill()
{
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Sse);
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Stdio);
    addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::StreamableHttp);
}

TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType SelectTypeComboBox::type() const
{
    return currentData().value<TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType>();
}

void SelectTypeComboBox::setType(TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType type)
{
    const int index = findData(QVariant::fromValue(type));
    if (index != -1) {
        setCurrentIndex(index);
    } else {
        setCurrentIndex(0);
    }
}

#include "moc_selecttypecombobox.cpp"
