/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QJsonObject>
#include <QList>
#include <QWidget>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientProtocolManager>
#include <functional>
class QComboBox;
class QLineEdit;
class QPlainTextEdit;
class QPushButton;
class QTimer;
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(const QString &url, QWidget *parent = nullptr);
    ~MainWidget() override;

    // Connect if necessary and run all checks
    void runAllChecks();

Q_SIGNALS:
    void checksFinished(int failureCount);

private:
    struct Check {
        QString name;
        // Send request, return request id
        std::function<qint64()> run;
        // Return error message, empty if response is valid
        std::function<QString(const QJsonObject &)> verify;
    };
    void connectToServer();
    void disconnectFromServer();
    void callTool();
    void slotReceived(const QJsonObject &obj, TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager::MethodType type);
    void updateButtons();
    void log(const QString &str);
    void fillTools(const QJsonObject &obj);
    void initializeChecks();
    void runNextCheck();
    void checkFinished(const QString &errorMessage);
    void finishChecks();
    void logRequest(const QString &action, qint64 id);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager *mManager = nullptr;
    QList<Check> mChecks;
    qsizetype mCurrentCheck = -1;
    qint64 mCurrentRequestId = -1;
    int mFailureCount = 0;
    bool mRunChecksWhenInitialized = false;
    QLineEdit *const mUrl;
    QPushButton *const mConnectButton;
    QPushButton *const mDisconnectButton;
    QPushButton *const mPingButton;
    QPushButton *const mListToolsButton;
    QPushButton *const mListPromptsButton;
    QPushButton *const mListResourceTemplatesButton;
    QPushButton *const mRunChecksButton;
    QComboBox *const mTools;
    QLineEdit *const mArguments;
    QPushButton *const mCallToolButton;
    QPlainTextEdit *const mLog;
    QTimer *const mCheckTimer;
};
