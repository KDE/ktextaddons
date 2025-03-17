/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutogenerateText
{
class TextAutogenerateResultWidget;
class TextAutogenerateTextLineEditWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateWidget(QWidget *parent = nullptr);
    ~TextAutogenerateWidget() override;

    [[nodiscard]] QString textLineEdit() const;

Q_SIGNALS:
    void editingFinished(const QString &str);

private:
    TextAutogenerateResultWidget *const mTextAutogenerateResultWidget;
    TextAutogenerateTextLineEditWidget *const mTextAutogenerateTextLineEditWidget;
};
}
