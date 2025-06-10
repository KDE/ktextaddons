/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class KMessageWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateNotWorkingMessageWidget;
/**
 * @brief The TextAutoGenerateNotWorkingWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateNotWorkingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateNotWorkingWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateNotWorkingWidget() override;

    void setMessageError(const QString &str);
    void clearMessage();

Q_SIGNALS:
    void ollamaStarted();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotStartOllama();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigure();
    TextAutoGenerateNotWorkingMessageWidget *const mMessageWidget;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
