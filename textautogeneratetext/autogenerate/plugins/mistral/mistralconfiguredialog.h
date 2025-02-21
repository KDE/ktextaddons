/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class MistralConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MistralConfigureDialog(QWidget *parent = nullptr);
    ~MistralConfigureDialog() override;
};
