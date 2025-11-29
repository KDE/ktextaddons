/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <QObject>
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT OpenFileJob : public QObject
{
    Q_OBJECT
public:
    explicit OpenFileJob(QObject *parent = nullptr);
    ~OpenFileJob() override;
};
}
