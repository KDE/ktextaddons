/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QTextEdit;
class EmoticonWidgetActionWidgetGui : public QWidget
{
    Q_OBJECT
public:
    explicit EmoticonWidgetActionWidgetGui(QWidget *parent = nullptr);
    ~EmoticonWidgetActionWidgetGui() override;

private:
    QTextEdit *const mTextEdit;
};
