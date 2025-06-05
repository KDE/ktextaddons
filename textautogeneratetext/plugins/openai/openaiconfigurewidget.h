/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QWidget>
#include <TextAutoGenerateText/NetworkPluginConfigureWidget>
class OpenAIConfigureWidget : public TextAutoGenerateText::NetworkPluginConfigureWidget
{
    Q_OBJECT
public:
    explicit OpenAIConfigureWidget(QWidget *parent = nullptr);
    ~OpenAIConfigureWidget() override;
};
