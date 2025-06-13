/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerategeneric_private_export.h"
#include <TextAutoGenerateText/TextAutoGenerateNetworkPluginConfigureWidget>
class GenericNetworkManager;
class TEXTAUTOGENERATEGENERICNETWORK_TESTS_EXPORT GenericNetworkNetworkPluginConfigureWidget
    : public TextAutoGenerateText::TextAutoGenerateNetworkPluginConfigureWidget
{
    Q_OBJECT
public:
    explicit GenericNetworkNetworkPluginConfigureWidget(GenericNetworkManager *manager, QWidget *parent = nullptr);
    ~GenericNetworkNetworkPluginConfigureWidget() override;
};
