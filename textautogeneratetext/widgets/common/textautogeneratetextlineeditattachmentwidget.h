/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateFlowLayout;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextLineEditAttachmentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextLineEditAttachmentWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextLineEditAttachmentWidget() override;

    void addAttachement(const QString &fileName);

private:
    TextAutoGenerateFlowLayout *const mMainLayout;
};
}
