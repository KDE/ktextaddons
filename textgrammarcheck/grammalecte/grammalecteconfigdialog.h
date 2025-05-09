/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textgrammarcheck_export.h"
#include <QDialog>
namespace TextGrammarCheck
{
class GrammalecteConfigWidget;
class TEXTGRAMMARCHECK_EXPORT GrammalecteConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GrammalecteConfigDialog(QWidget *parent = nullptr, bool disableMessageBox = false);
    ~GrammalecteConfigDialog() override;

private:
    Q_DISABLE_COPY(GrammalecteConfigDialog)
    TEXTGRAMMARCHECK_NO_EXPORT void writeConfig();
    TEXTGRAMMARCHECK_NO_EXPORT void readConfig();
    GrammalecteConfigWidget *const mConfigWidget;
};
}
