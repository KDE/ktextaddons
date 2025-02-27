/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextclient.h"
#include <KLocalizedString>
using namespace TextAutogenerateText;
TextAutogenerateTextClient::TextAutogenerateTextClient(QObject *parent)
    : QObject{parent}
{
}

TextAutogenerateTextClient::~TextAutogenerateTextClient() = default;

bool TextAutogenerateTextClient::hasConfigurationDialog() const
{
    return false;
}

bool TextAutogenerateTextClient::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget);
    // Nothing by default
    return false;
}

QString TextAutogenerateTextClient::convertEngineType(TextAutogenerateText::TextAutogenerateTextClient::EngineType type)
{
    switch (type) {
    case TextAutogenerateText::TextAutogenerateTextClient::EngineType::Local:
        return i18n("Local");
    case TextAutogenerateText::TextAutogenerateTextClient::EngineType::Network:
        return i18n("Network");
    }
    Q_UNREACHABLE();
    return {};
}

#include "moc_textautogeneratetextclient.cpp"
