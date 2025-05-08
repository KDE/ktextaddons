/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextclient.h"
#include <KLocalizedString>
using namespace TextAutogenerateText;
TextAutoGenerateTextClient::TextAutoGenerateTextClient(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextClient::~TextAutoGenerateTextClient() = default;

bool TextAutoGenerateTextClient::hasConfigurationDialog() const
{
    return false;
}

bool TextAutoGenerateTextClient::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget);
    // Nothing by default
    return false;
}

QString TextAutoGenerateTextClient::convertEngineType(TextAutogenerateText::TextAutoGenerateTextClient::EngineType type)
{
    switch (type) {
    case TextAutogenerateText::TextAutoGenerateTextClient::EngineType::Local:
        return i18n("Local");
    case TextAutogenerateText::TextAutoGenerateTextClient::EngineType::Network:
        return i18n("Network");
    }
    Q_UNREACHABLE();
    return {};
}

#include "moc_textautogeneratetextclient.cpp"
