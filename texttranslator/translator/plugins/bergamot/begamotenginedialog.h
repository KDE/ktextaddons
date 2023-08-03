/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>

class BegamotEngineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BegamotEngineDialog(QWidget *parent = nullptr);
    ~BegamotEngineDialog() override;
};
