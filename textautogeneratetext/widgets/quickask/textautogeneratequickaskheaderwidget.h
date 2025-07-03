/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLabel;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateTextModelComboBox;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateQuickAskHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickAskHeaderWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateQuickAskHeaderWidget() override;

    void updateEngineModelName(const QString &str);

Q_SIGNALS:
    void configureRequested();

private:
    QLabel *const mModelInstanceLabel;
    TextAutoGenerateTextModelComboBox *const mModelComboBox;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
