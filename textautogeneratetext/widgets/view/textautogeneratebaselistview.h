/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateBaseListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateBaseListView(QWidget *parent = nullptr);
    ~TextAutoGenerateBaseListView() override;
};
}
