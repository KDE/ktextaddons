/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QLineEdit;
class OllamaModelSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelSearchWidget(QWidget *parent = nullptr);
    ~OllamaModelSearchWidget() override;

private:
    QLineEdit *const mSearchLineEdit;
};
