/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <TextGrammarCheck/GrammarResultWidget>
namespace TextGrammarCheck
{
class LanguageToolComboBox;
class LanguageToolUpdateComboBox;
/*!
 * \class TextGrammarCheck::LanguageToolResultWidget
 * \inheaderfile TextGrammarCheck/LanguageToolResultWidget
 * \inmodule TextGrammarCheck
 * \brief Widget displaying LanguageTool grammar check results.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT LanguageToolResultWidget : public GrammarResultWidget
{
    Q_OBJECT
public:
    /*! Constructs a new LanguageToolResultWidget. */
    explicit LanguageToolResultWidget(QWidget *parent = nullptr);
    /*! Destroys the widget. */
    ~LanguageToolResultWidget() override;
    /*! Checks the grammar of the text. */
    void checkGrammar() override;

protected:
    /*! Adds extra widgets to the result display. */
    void addExtraWidget() override;

private:
    Q_DISABLE_COPY(LanguageToolResultWidget)
    TEXTGRAMMARCHECK_NO_EXPORT void slotCheckGrammarFinished(const QString &result);
    TEXTGRAMMARCHECK_NO_EXPORT void slotError(const QString &str);
    LanguageToolComboBox *mLanguageToolComboBox = nullptr;
    LanguageToolUpdateComboBox *const mLanguageToolUpdateCombobox;
};
}
