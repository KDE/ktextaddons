/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateText/TextAutoGenerateNetworkPluginConfigureWidget>
class MistralConfigureWidget : public TextAutoGenerateText::TextAutoGenerateNetworkPluginConfigureWidget
{
    Q_OBJECT
public:
    explicit MistralConfigureWidget(QWidget *parent = nullptr);
    ~MistralConfigureWidget() override;
};
