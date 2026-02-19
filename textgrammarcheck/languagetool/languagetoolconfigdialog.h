/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textgrammarcheck_export.h"
#include <QDialog>
namespace TextGrammarCheck
{
class LanguageToolConfigWidget;
/*!
 * \class TextGrammarCheck::LanguageToolConfigDialog
 * \inheaderfile TextGrammarCheck/LanguageToolConfigDialog
 * \inmodule TextGrammarCheck
 * \brief Configuration dialog for LanguageTool grammar checker.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT LanguageToolConfigDialog : public QDialog
{
    Q_OBJECT
public:
    /*! Constructs a new LanguageToolConfigDialog. */
    explicit LanguageToolConfigDialog(QWidget *parent = nullptr);
    /*! Destroys the dialog. */
    ~LanguageToolConfigDialog() override;

private:
    Q_DISABLE_COPY(LanguageToolConfigDialog)
    TEXTGRAMMARCHECK_NO_EXPORT void writeConfig();
    TEXTGRAMMARCHECK_NO_EXPORT void readConfig();
    LanguageToolConfigWidget *const mConfigWidget;
};
}
