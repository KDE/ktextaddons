/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>

namespace TextAddonsWidgets
{
class WhatsNewNgWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WhatsNewNgWidget(QWidget *parent = nullptr);
    ~WhatsNewNgWidget() override;
};
}
