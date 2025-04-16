/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLabel;
class QToolButton;
namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateHeaderWidget(QWidget *parent = nullptr);
    ~TextAutogenerateHeaderWidget() override;
    void updateEngineName(const QString &engineName);

Q_SIGNALS:
    void configChanged();
    void clearModel();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureEngine();
    QLabel *const mEngineName;
    QToolButton *const mConfigureEngine;
    QToolButton *const mClearChat;
};
}
