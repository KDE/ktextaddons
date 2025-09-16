/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateToolPluginShowMetaDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolPluginShowMetaDataWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateToolPluginShowMetaDataWidget() override;
};
}
