/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateSearchWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateSearchDialog() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateSearchWidget *const mTextAutoGenerateSearchWidget;
};
}
