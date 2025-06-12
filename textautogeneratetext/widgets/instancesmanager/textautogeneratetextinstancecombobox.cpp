/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancecombobox.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogeneratemanager.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceComboBox::TextAutoGenerateTextInstanceComboBox(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QComboBox(parent)
    , mManager(manager)
{
    if (mManager) {
        fillEngine();
    }
}

TextAutoGenerateTextInstanceComboBox::~TextAutoGenerateTextInstanceComboBox() = default;

void TextAutoGenerateTextInstanceComboBox::fillEngine()
{
    clear();
    const QList<TextAutoGenerateTextClient::SupportedServer> list = mManager->textAutoGenerateEngineLoader()->supportedServers();
    for (const auto &info : list) {
        addItem(info.localizedName, QVariant::fromValue(info));
    }
}

TextAutoGenerateTextClient::SupportedServer TextAutoGenerateTextInstanceComboBox::selectedInstanceType() const
{
    return currentData().value<TextAutoGenerateTextClient::SupportedServer>();
}

#include "moc_textautogeneratetextinstancecombobox.cpp"
