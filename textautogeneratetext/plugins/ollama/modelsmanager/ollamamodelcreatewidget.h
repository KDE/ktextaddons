/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaManager;
class QStackedWidget;
class OllamaModelCreateFromExistingModelWidget;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelCreateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelCreateWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelCreateWidget() override;

Q_SIGNALS:
    void createModelDone();

private:
    OllamaManager *const mManager;
    QStackedWidget *const mStackWidget;
    OllamaModelCreateFromExistingModelWidget *const mOllamaModelCreateFromExistingModelWidget;
    QWidget *const mSelectModeWidget;
};
