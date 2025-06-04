/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class QLineEdit;
class OllamaManager;
class QPlainTextEdit;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelCreateFromExistingModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelCreateFromExistingModelWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelCreateFromExistingModelWidget() override;

Q_SIGNALS:
    void cancelRequested();
    void createNewModelRequested();

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotCreateModel();
    QLineEdit *const mModelName;
    QLineEdit *const mTagName;
    OllamaManager *const mOllamaManager;
    QPlainTextEdit *const mPromptPlainTextEdit;
};
