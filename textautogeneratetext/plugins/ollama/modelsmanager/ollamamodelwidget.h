/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaModelSearchWidget;
class OllamaModelListView;
class OllamaModelInfoWidget;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelWidget(QWidget *parent = nullptr);
    ~OllamaModelWidget() override;

private:
    OllamaModelSearchWidget *const mSearchWidget;
    OllamaModelListView *const mListView;
    OllamaModelInfoWidget *const mInfoWidget;
};
