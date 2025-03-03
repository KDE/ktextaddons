/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
namespace TextAutogenerateText
{
class TextAutogenerateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateWidget(QWidget *parent = nullptr);
    ~TextAutogenerateWidget() override;
};
}
