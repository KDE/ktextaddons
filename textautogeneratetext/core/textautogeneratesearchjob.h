/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include "textautogeneratetext_private_export.h"
namespace TextAutoGenerateText
{
class TextAutoGenerateSearchWidget;
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchJob(QObject *parent = nullptr);
    ~TextAutoGenerateSearchJob() override;
};
}
