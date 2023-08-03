/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_export.h"
#include <QObject>

class LIBBERGAMOT_EXPORT ManagerModelTranslator : public QObject
{
    Q_OBJECT
public:
    explicit ManagerModelTranslator(QObject *parent = nullptr);
    ~ManagerModelTranslator() override;

    void downloadListModels();

private:
    LIBBERGAMOT_NO_EXPORT void parseListModel(const QJsonObject &obj);
};
