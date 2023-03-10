/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

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
    void writeConfig();
    void readConfig();
    GrammalecteConfigWidget *const mConfigWidget;
};
}
