/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "widgets/view/textautogeneratelistviewbasedelegate.h"
#include <QObject>

class OllamaModelInfosDelegate : public TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit OllamaModelInfosDelegate(QListView *view);
    ~OllamaModelInfosDelegate() override;

    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const override;
};
