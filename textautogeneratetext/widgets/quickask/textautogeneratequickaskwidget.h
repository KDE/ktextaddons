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
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadEngine();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditingFinished(const QString &str, const QByteArray &uuid);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFailed(const QString &str);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotInitializeDone();
    QStackedWidget *const mStackedWidget;
    TextAutoGenerateQuickAskViewWidget *const mTextAutoGenerateQuickAskViewWidget;
    TextAutoGenerateNotWorkingWidget *const mTextAutoGenerateNotWorkingWidget;
    TextAutoGenerateManager *const mManager;
    QStringList mAskMessageList;
    bool mPluginWasInitialized = false;
};
}
