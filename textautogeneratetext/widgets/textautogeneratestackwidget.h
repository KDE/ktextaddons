/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QStackedWidget;
namespace TextAutogenerateText
{
class TextAutogenerateNotWorkingWidget;
class TextAutogenerateWidget;
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateStackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateStackWidget(QWidget *parent = nullptr);
    ~TextAutogenerateStackWidget() override;

    void setBrokenEngine(bool state, const QString &errorMessage);

private:
    QStackedWidget *const mStackedWidget;
    TextAutogenerateNotWorkingWidget *const mTextAutogenerateNotWorkingWidget;
    TextAutogenerateWidget *const mTextAutogenerateWidget;
};

}
