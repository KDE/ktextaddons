/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libbergamot_private_export.h"
#include <QAbstractListModel>

class LIBBERGAMOT_TESTS_EXPORT TranslatorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TranslatorModel(QObject *parent = nullptr);
    ~TranslatorModel() override;
};
