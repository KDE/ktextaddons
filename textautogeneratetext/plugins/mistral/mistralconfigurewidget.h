/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateText/NetworkConfigureWidget>
class MistralConfigureWidget : public TextAutoGenerateText::NetworkConfigureWidget
{
    Q_OBJECT
public:
    explicit MistralConfigureWidget(QWidget *parent = nullptr);
    ~MistralConfigureWidget() override;
};
