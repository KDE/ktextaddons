/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAskJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAskJob(QObject *parent = nullptr);
    ~TextAutoGenerateAskJob() override;
};
}
