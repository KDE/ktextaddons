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

void SelectTypeComboBox::fill()
{
    addItem(i18n("Sse"), QVariant::fromValue(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType::Sse));
    addItem(i18n("Stdio"), QVariant::fromValue(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType::Stdio));
    addItem(i18n("Streamble Http"), QVariant::fromValue(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType::StreamableHttp));
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType SelectTypeComboBox::type() const
{
    return currentData().value<TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType>();
}

void SelectTypeComboBox::setType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType type)
{
    const int index = findData(QVariant::fromValue(type));
    if (index != -1) {
        setCurrentIndex(index);
    } else {
        setCurrentIndex(0);
    }
}

#include "moc_selecttypecombobox.cpp"
