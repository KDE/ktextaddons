/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateShowDebugWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateShowDebugDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowDebugDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateShowDebugDialog() override;

    void setPlainText(const QString &text);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateShowDebugWidget *const mShowDebugWidget;
};
}
