/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <KTextEdit>
namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateTextLineEdit : public KTextEdit
{
    Q_OBJECT
public:
    explicit TextAutogenerateTextLineEdit(QWidget *parent = nullptr);
    ~TextAutogenerateTextLineEdit() override;

    [[nodiscard]] QString text() const;

    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] QSize minimumSizeHint() const override;
Q_SIGNALS:
    void sendMessage(const QString &);
    void keyPressed(QKeyEvent *ev);

protected:
    void keyPressEvent(QKeyEvent *e) override;
};
}
