/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLabel;
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHeaderWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateHeaderWidget() override;
    void updateEngineName(const QString &engineName);

Q_SIGNALS:
    void configChanged();
    void addNewChat();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureEngine();
    QLabel *const mEngineName;
    QToolButton *const mConfigureEngine;
    QToolButton *const mNewChat;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
