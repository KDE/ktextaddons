/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_private_export.h"
#include <QWidget>
class QTreeView;

class LIBBERGAMOT_TESTS_EXPORT BergamotEngineLanguageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BergamotEngineLanguageWidget(QWidget *parent = nullptr);
    ~BergamotEngineLanguageWidget() override;

private:
    QTreeView *const mTreeView;
};
