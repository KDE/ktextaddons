/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QPushButton;
namespace TextAutogenerateText
{
class TextAutogenerateTextLineEdit;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateTextLineEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateTextLineEditWidget(QWidget *parent = nullptr);
    ~TextAutogenerateTextLineEditWidget() override;

    [[nodiscard]] QString text() const;

    [[nodiscard]] QByteArray uuid() const;
    void setUuid(const QByteArray &newUuid);

    void setText(const QString &str);
Q_SIGNALS:
    void editingFinished(const QString &str, const QByteArray &uuid);
    void keyPressed(QKeyEvent *ev);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void clearLineEdit();
    TextAutogenerateTextLineEdit *const mTextAutogenerateTextLineEdit;
    QPushButton *const mSendMessage;
    QByteArray mUuid;
};
}
