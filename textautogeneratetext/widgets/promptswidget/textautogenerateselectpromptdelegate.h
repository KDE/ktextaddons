/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QItemDelegate>
namespace TextAutoGenerateText
{
class TextAutoGenerateSelectPromptDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectPromptDelegate(QObject *parent = nullptr);
    ~TextAutoGenerateSelectPromptDelegate() override;
};
}
