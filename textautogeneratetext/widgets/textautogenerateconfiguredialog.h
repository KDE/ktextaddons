/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateConfigureWidget;
/**
 * @brief The TextAutoGenerateConfigureDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateConfigureDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateConfigureDialog() override;

    void saveSettings();

private:
    TextAutoGenerateConfigureWidget *const mTextAutoGenerateConfigureWidget;
};
}
