/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class QPlainTextEdit;
class OllamaLogDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OllamaLogDialog(QWidget *parent = nullptr);
    ~OllamaLogDialog() override;

    void setLog(const QByteArray &ba);

private:
    void readConfig();
    void writeConfig();
    QPlainTextEdit *const mPlainTextEdit;
};
