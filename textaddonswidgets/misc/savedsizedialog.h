/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textaddonswidgets_export.h"
#include <QDialog>
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT SavedSizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SavedSizeDialog(QLatin1StringView configGroupName, QSize defaultSize, QWidget *parent = nullptr);
    ~SavedSizeDialog() override;

protected:
    void showEvent(QShowEvent *event) override;

private:
    QString mConfigGroupName;
    QSize mDefaultSize;
    bool mWasInitialized = false;
};
}
