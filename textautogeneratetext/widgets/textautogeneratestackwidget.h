/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QStackedWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateNotWorkingWidget;
class TextAutoGenerateNotInstanceFoundWidget;
class TextAutoGenerateManager;
class TextAutoGenerateWidget;
/**
 * @brief The TextAutoGenerateStackWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateStackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateStackWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateStackWidget() override;

    void setBrokenEngine(bool state, const QString &errorMessage);
    void slotSearchText();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotNeedToAddInstances();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureInstances();
    QStackedWidget *const mStackedWidget;
    TextAutoGenerateNotWorkingWidget *const mTextAutoGenerateNotWorkingWidget;
    TextAutoGenerateNotInstanceFoundWidget *const mTextAutoGenerateNotInstanceFoundWidget;
    TextAutoGenerateWidget *const mTextAutoGenerateWidget;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};

}
