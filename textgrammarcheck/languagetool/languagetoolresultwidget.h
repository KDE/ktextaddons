/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <TextGrammarCheck/GrammarResultWidget>
namespace TextGrammarCheck
{
class LanguageToolComboBox;
class LanguageToolUpdateComboBox;
class TEXTGRAMMARCHECK_EXPORT LanguageToolResultWidget : public GrammarResultWidget
{
    Q_OBJECT
public:
    explicit LanguageToolResultWidget(QWidget *parent = nullptr);
    ~LanguageToolResultWidget() override;
    void checkGrammar() override;

protected:
    void addExtraWidget() override;

private:
    Q_DISABLE_COPY(LanguageToolResultWidget)
    TEXTGRAMMARCHECK_NO_EXPORT void slotCheckGrammarFinished(const QString &result);
    TEXTGRAMMARCHECK_NO_EXPORT void slotError(const QString &str);
    LanguageToolComboBox *mLanguageToolComboBox = nullptr;
    LanguageToolUpdateComboBox *const mLanguageToolUpdateCombobox;
};
}
