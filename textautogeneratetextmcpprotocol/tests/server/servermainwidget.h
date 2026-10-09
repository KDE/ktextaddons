/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QLineEdit;
class QPlainTextEdit;
class QPushButton;
class McpTestServer;
class ServerMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ServerMainWidget(const QString &url, QWidget *parent = nullptr);
    ~ServerMainWidget() override;

    void startServer();

private:
    void updateButtons(bool running);
    McpTestServer *const mServer;
    QLineEdit *const mUrl;
    QPushButton *const mStartButton;
    QPushButton *const mStopButton;
    QPushButton *const mToggleToolButton;
    QPushButton *const mPingButton;
    QPlainTextEdit *const mLog;
};
