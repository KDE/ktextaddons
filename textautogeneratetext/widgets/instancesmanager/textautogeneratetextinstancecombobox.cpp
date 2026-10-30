/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancecombobox.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceComboBox::TextAutoGenerateTextInstanceComboBox(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QComboBox(parent)
    , mManager(manager)
{
    if (mManager) {
        fillEngine();
        connect(mManager->textAutoGenerateTextInstancesManager(),
                &TextAutoGenerateTextInstancesManager::instanceFilterChanged,
                this,
                &TextAutoGenerateTextInstanceComboBox::fillEngine);
    }
}

TextAutoGenerateTextInstanceComboBox::~TextAutoGenerateTextInstanceComboBox() = default;

void TextAutoGenerateTextInstanceComboBox::fillEngine()
{
    clear();
    const bool localOnly =
        mManager->textAutoGenerateTextInstancesManager()->instanceFilter() == TextAutoGenerateTextInstancesManager::InstanceFilter::LocalOnly;
    const QList<TextAutoGenerateTextClient::SupportedServer> list = mManager->textAutoGenerateEngineLoader()->supportedServers();
    for (const auto &info : list) {
        if (localOnly && !info.isLocalServer) {
            continue;
        }
        addItem(info.localizedName, QVariant::fromValue(info));
    }
}

TextAutoGenerateTextClient::SupportedServer TextAutoGenerateTextInstanceComboBox::selectedInstanceType() const
{
    return currentData().value<TextAutoGenerateTextClient::SupportedServer>();
}

#include "moc_textautogeneratetextinstancecombobox.cpp"
