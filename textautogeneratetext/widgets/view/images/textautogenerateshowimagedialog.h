/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateShowImageWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateShowImageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowImageDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateShowImageDialog() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateShowImageWidget *const mShowImageWidget;
};
}
