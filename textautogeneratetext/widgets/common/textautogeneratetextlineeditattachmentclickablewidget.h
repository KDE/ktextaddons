/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QLabel>
#include <QWidget>
namespace TextAutoGenerateText
{

class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextLineEditAttachmentClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextLineEditAttachmentClickableLabel(QWidget *parent = nullptr);
    ~TextAutoGenerateTextLineEditAttachmentClickableLabel() override;

Q_SIGNALS:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextLineEditAttachmentClickableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextLineEditAttachmentClickableWidget(const QString &fileName, QWidget *parent = nullptr);
    ~TextAutoGenerateTextLineEditAttachmentClickableWidget() override;

Q_SIGNALS:
    void remove();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemove();
    QString mFileName;
    TextAutoGenerateTextLineEditAttachmentClickableLabel *const mClickableLabel;
    QLabel *const mFileNameLabel;
};
}
