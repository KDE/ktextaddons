/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "libbergamot_export.h"
#include <QDialog>
class BergamotEngineWidget;
class LIBBERGAMOT_EXPORT BegamotEngineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BegamotEngineDialog(QWidget *parent = nullptr);
    ~BegamotEngineDialog() override;

private:
    LIBBERGAMOT_NO_EXPORT void writeConfig();
    LIBBERGAMOT_NO_EXPORT void readConfig();
    BergamotEngineWidget *const mBergamotEngineWidget;
};
