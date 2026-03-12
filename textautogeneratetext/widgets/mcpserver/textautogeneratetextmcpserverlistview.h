/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextMcpServerListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextMcpServerListView(QWidget *parent = nullptr);
    ~TextAutoGenerateTextMcpServerListView() override;
};
}
