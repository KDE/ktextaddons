/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textgrammarcheck_export.h"
#include <QDialog>
namespace TextGrammarCheck
{
class LanguageToolConfigWidget;
class TEXTGRAMMARCHECK_EXPORT LanguageToolConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LanguageToolConfigDialog(QWidget *parent = nullptr);
    ~LanguageToolConfigDialog() override;

private:
    Q_DISABLE_COPY(LanguageToolConfigDialog)
    TEXTGRAMMARCHECK_NO_EXPORT void writeConfig();
    TEXTGRAMMARCHECK_NO_EXPORT void readConfig();
    LanguageToolConfigWidget *const mConfigWidget;
};
}
