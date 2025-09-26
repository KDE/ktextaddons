/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QTextEdit>
#include <QWidget>
class EmoticonWidgetTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit EmoticonWidgetTextEdit(QWidget *parent = nullptr);
    ~EmoticonWidgetTextEdit() override;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

class EmoticonWidgetActionWidgetGui : public QWidget
{
    Q_OBJECT
public:
    explicit EmoticonWidgetActionWidgetGui(QWidget *parent = nullptr);
    ~EmoticonWidgetActionWidgetGui() override;

private:
    EmoticonWidgetTextEdit *const mTextEdit;
};
