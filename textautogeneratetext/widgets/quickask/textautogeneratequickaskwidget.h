/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QWidget>
class QStackedWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateQuickAskViewWidget;
class TextAutoGenerateManager;
class TextAutoGenerateNotWorkingWidget;
/**
 * @brief The TextAutoGenerateQuickAskWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateQuickAskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickAskWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateQuickAskWidget() override;

private:
    QStackedWidget *const mStackedWidget;
    TextAutoGenerateQuickAskViewWidget *const mTextAutoGenerateQuickAskViewWidget;
    TextAutoGenerateNotWorkingWidget *const mTextAutoGenerateNotWorkingWidget;
};
}
