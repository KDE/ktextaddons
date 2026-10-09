/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "mainwidget.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QMetaEnum>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTextStream>
#include <QTimer>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
using namespace Qt::Literals::StringLiterals;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager;
using MethodType = TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager::MethodType;
namespace
{
constexpr auto checkTimeout = std::chrono::seconds(10);
// Request timeout used to check that client cancels "slow" tool
constexpr auto shortRequestTimeout = std::chrono::milliseconds(1000);
constexpr auto defaultRequestTimeout = std::chrono::seconds(60);

QString compact(const QJsonObject &obj)
{
    return QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

QString errorMessage(const QJsonObject &obj)
{
    if (obj.contains("error"_L1)) {
        return u"Error response: %1"_s.arg(compact(obj.value("error"_L1).toObject()));
    }
    if (!obj.value("result"_L1).isObject()) {
        return u"No result"_s;
    }
    return {};
}

// Text of first content of a CallToolResult
QString toolText(const QJsonObject &obj)
{
    return obj.value("result"_L1).toObject().value("content"_L1).toArray().at(0).toObject().value("text"_L1).toString();
}

bool toolIsError(const QJsonObject &obj)
{
    return obj.value("result"_L1).toObject().value("isError"_L1).toBool();
}

QStringList names(const QJsonObject &obj, const QString &key)
{
    QStringList list;
    const QJsonArray array = obj.value("result"_L1).toObject().value(key).toArray();
    for (const auto &value : array) {
        list.append(value.toObject().value("name"_L1).toString());
    }
    return list;
}
}

MainWidget::MainWidget(const QString &url, QWidget *parent)
    : QWidget{parent}
    , mUrl(new QLineEdit(url, this))
    , mConnectButton(new QPushButton(u"Connect"_s, this))
    , mDisconnectButton(new QPushButton(u"Disconnect"_s, this))
    , mPingButton(new QPushButton(u"Ping"_s, this))
    , mListToolsButton(new QPushButton(u"List tools"_s, this))
    , mListPromptsButton(new QPushButton(u"List prompts"_s, this))
    , mListResourceTemplatesButton(new QPushButton(u"List resource templates"_s, this))
    , mRunChecksButton(new QPushButton(u"Run all checks"_s, this))
    , mTools(new QComboBox(this))
    , mArguments(new QLineEdit(this))
    , mCallToolButton(new QPushButton(u"Call tool"_s, this))
    , mLog(new QPlainTextEdit(this))
    , mCheckTimer(new QTimer(this))
{
    auto mainLayout = new QVBoxLayout(this);

    auto urlLayout = new QHBoxLayout;
    urlLayout->addWidget(new QLabel(u"Server url:"_s, this));
    urlLayout->addWidget(mUrl);
    urlLayout->addWidget(mConnectButton);
    urlLayout->addWidget(mDisconnectButton);
    mainLayout->addLayout(urlLayout);

    auto actionLayout = new QHBoxLayout;
    actionLayout->addWidget(mPingButton);
    actionLayout->addWidget(mListToolsButton);
    actionLayout->addWidget(mListPromptsButton);
    actionLayout->addWidget(mListResourceTemplatesButton);
    actionLayout->addStretch();
    actionLayout->addWidget(mRunChecksButton);
    mainLayout->addLayout(actionLayout);

    auto toolLayout = new QHBoxLayout;
    toolLayout->addWidget(new QLabel(u"Tool:"_s, this));
    mTools->setEditable(true);
    mTools->setMinimumContentsLength(15);
    toolLayout->addWidget(mTools);
    toolLayout->addWidget(new QLabel(u"Arguments (JSON):"_s, this));
    mArguments->setPlaceholderText(uR"({"text": "hello"})"_s);
    toolLayout->addWidget(mArguments, 1);
    toolLayout->addWidget(mCallToolButton);
    mainLayout->addLayout(toolLayout);

    mLog->setReadOnly(true);
    mainLayout->addWidget(mLog);

    mCheckTimer->setSingleShot(true);
    mCheckTimer->setInterval(checkTimeout);
    connect(mCheckTimer, &QTimer::timeout, this, [this]() {
        checkFinished(u"No response"_s);
    });

    connect(mConnectButton, &QPushButton::clicked, this, &MainWidget::connectToServer);
    connect(mDisconnectButton, &QPushButton::clicked, this, &MainWidget::disconnectFromServer);
    connect(mPingButton, &QPushButton::clicked, this, [this]() {
        logRequest(u"ping"_s, mManager->executeAction(MethodType::Ping));
    });
    connect(mListToolsButton, &QPushButton::clicked, this, [this]() {
        logRequest(u"tools/list"_s, mManager->executeAction(MethodType::ListTools));
    });
    connect(mListPromptsButton, &QPushButton::clicked, this, [this]() {
        logRequest(u"prompts/list"_s, mManager->executeAction(MethodType::ListPrompts));
    });
    connect(mListResourceTemplatesButton, &QPushButton::clicked, this, [this]() {
        logRequest(u"resources/templates/list"_s, mManager->executeAction(MethodType::ResourceTemplates));
    });
    connect(mCallToolButton, &QPushButton::clicked, this, &MainWidget::callTool);
    connect(mRunChecksButton, &QPushButton::clicked, this, &MainWidget::runAllChecks);
    initializeChecks();
    updateButtons();
}

MainWidget::~MainWidget() = default;

void MainWidget::log(const QString &str)
{
    mLog->appendPlainText(str);
}

void MainWidget::logRequest(const QString &action, qint64 id)
{
    if (id < 0) {
        log(u"FAILED to send %1 (see debug output)"_s.arg(action));
    } else {
        log(u"--> %1 (id %2)"_s.arg(action).arg(id));
    }
}

void MainWidget::updateButtons()
{
    const bool started = mManager != nullptr;
    const bool initialized = started && mManager->isInitialized();
    const bool checking = mCurrentCheck >= 0;
    mUrl->setEnabled(!started);
    mConnectButton->setEnabled(!started);
    mDisconnectButton->setEnabled(started && !checking);
    mPingButton->setEnabled(started && !checking);
    mListToolsButton->setEnabled(initialized && !checking);
    mListPromptsButton->setEnabled(initialized && !checking);
    mListResourceTemplatesButton->setEnabled(initialized && !checking);
    mCallToolButton->setEnabled(initialized && !checking);
    mRunChecksButton->setEnabled(!checking && !mRunChecksWhenInitialized);
}

void MainWidget::connectToServer()
{
    if (mManager) {
        return;
    }
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"test server"_s);
    server.createUniqueIdentifier();
    server.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(QUrl(mUrl->text().trimmed()));
    server.setSettings(settings);

    mManager = new McpProtocolClientProtocolManager(server, this);
    mManager->setClientName(u"mcpclient_gui"_s);
    connect(mManager, &McpProtocolClientProtocolManager::started, this, [this]() {
        log(u"Client started, initializing…"_s);
    });
    connect(mManager, &McpProtocolClientProtocolManager::initialized, this, [this]() {
        const auto result = mManager->initializeResult();
        log(u"Initialized: server \"%1\" %2, protocol %3"_s.arg(result.serverInfo().name(), result.serverInfo().version(), result.protocolVersion()));
        updateButtons();
        if (std::exchange(mRunChecksWhenInitialized, false)) {
            runAllChecks();
        }
    });
    connect(mManager, &McpProtocolClientProtocolManager::received, this, &MainWidget::slotReceived);
    connect(mManager, &McpProtocolClientProtocolManager::error, this, [this](const QString &str) {
        log(u"ERROR: %1"_s.arg(str));
        // Manager doesn't stop client when initialize request failed
        if (!mManager->isInitialized()) {
            mManager->stopClient();
        }
    });
    connect(mManager, &McpProtocolClientProtocolManager::toolsListChanged, this, [this]() {
        log(u"Tools list changed: reload it"_s);
        if (mCurrentCheck < 0) {
            logRequest(u"tools/list"_s, mManager->executeAction(MethodType::ListTools));
        }
    });
    connect(mManager, &McpProtocolClientProtocolManager::finished, this, [this]() {
        log(u"Client finished"_s);
        if (mCurrentCheck >= 0) {
            checkFinished(u"Client finished"_s);
        }
        if (std::exchange(mRunChecksWhenInitialized, false)) {
            log(u"FAIL: impossible to connect to server"_s);
            mFailureCount = 1;
            finishChecks();
        }
        // Don't delete manager in its signal
        mManager->deleteLater();
        mManager = nullptr;
        mTools->clear();
        updateButtons();
    });
    log(u"Connecting to %1"_s.arg(settings.serverUrl().toString()));
    mManager->initializeClient();
    if (mManager && !mManager->isInitialized()) {
        updateButtons();
    }
}

void MainWidget::disconnectFromServer()
{
    if (mManager) {
        mManager->stopClient();
    }
}

void MainWidget::callTool()
{
    const QString name = mTools->currentText().trimmed();
    QJsonObject arguments;
    if (const QString text = mArguments->text().trimmed(); !text.isEmpty()) {
        QJsonParseError parseError;
        const QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &parseError);
        if (!doc.isObject()) {
            log(u"Invalid arguments: %1"_s.arg(parseError.error == QJsonParseError::NoError ? u"not a JSON object"_s : parseError.errorString()));
            return;
        }
        arguments = doc.object();
    }
    logRequest(u"tools/call %1 %2"_s.arg(name, compact(arguments)), mManager->callTool(name, arguments));
}

void MainWidget::fillTools(const QJsonObject &obj)
{
    const QString current = mTools->currentText();
    mTools->clear();
    const QJsonArray tools = obj.value("result"_L1).toObject().value("tools"_L1).toArray();
    for (const auto &value : tools) {
        const QJsonObject tool = value.toObject();
        mTools->addItem(tool.value("name"_L1).toString());
        mTools->setItemData(mTools->count() - 1,
                            u"%1\n%2"_s.arg(tool.value("description"_L1).toString(), compact(tool.value("inputSchema"_L1).toObject())),
                            Qt::ToolTipRole);
    }
    mTools->setCurrentText(current);
}

void MainWidget::slotReceived(const QJsonObject &obj, MethodType type)
{
    log(u"<-- [%1] %2"_s.arg(QString::fromLatin1(QMetaEnum::fromType<MethodType>().valueToKey(static_cast<int>(type))), compact(obj)));
    if (type == MethodType::ListTools && obj.contains("result"_L1)) {
        fillTools(obj);
    }
    if (mCurrentCheck >= 0 && type != MethodType::ServerRequest && type != MethodType::ServerNotification
        && obj.value("id"_L1).toInteger(-1) == mCurrentRequestId) {
        checkFinished(mChecks.at(mCurrentCheck).verify(obj));
    }
}

void MainWidget::initializeChecks()
{
    const auto toolCall = [this](const QString &name, const QJsonObject &arguments = {}) {
        return [this, name, arguments]() {
            return mManager->callTool(name, arguments);
        };
    };
    mChecks = {
        {u"Ping"_s,
         [this]() {
             return mManager->executeAction(MethodType::Ping);
         },
         errorMessage},
        {u"List tools (3 pages)"_s,
         [this]() {
             return mManager->executeAction(MethodType::ListTools);
         },
         [](const QJsonObject &obj) {
             if (const QString error = errorMessage(obj); !error.isEmpty()) {
                 return error;
             }
             const QStringList expected{u"echo"_s, u"add"_s, u"current_time"_s, u"fail"_s, u"slow"_s};
             const QStringList tools = names(obj, u"tools"_s);
             for (const QString &name : expected) {
                 if (!tools.contains(name)) {
                     return u"Tool \"%1\" is missing in %2"_s.arg(name, tools.join(u", "_s));
                 }
             }
             return QString();
         }},
        {u"Call echo"_s,
         toolCall(u"echo"_s, QJsonObject{{"text"_L1, u"Hello MCP"_s}}),
         [](const QJsonObject &obj) {
             if (const QString error = errorMessage(obj); !error.isEmpty()) {
                 return error;
             }
             return toolText(obj) == "Hello MCP"_L1 ? QString() : u"Unexpected text: %1"_s.arg(toolText(obj));
         }},
        {u"Call add (2 + 3)"_s,
         toolCall(u"add"_s, QJsonObject{{"a"_L1, 2}, {"b"_L1, 3}}),
         [](const QJsonObject &obj) {
             if (const QString error = errorMessage(obj); !error.isEmpty()) {
                 return error;
             }
             return toolText(obj) == "5"_L1 ? QString() : u"Unexpected result: %1"_s.arg(toolText(obj));
         }},
        {u"Call current_time"_s,
         toolCall(u"current_time"_s),
         [](const QJsonObject &obj) {
             if (const QString error = errorMessage(obj); !error.isEmpty()) {
                 return error;
             }
             return toolText(obj).isEmpty() || toolIsError(obj) ? u"Invalid result"_s : QString();
         }},
        {u"Call fail (isError)"_s,
         toolCall(u"fail"_s),
         [](const QJsonObject &obj) {
             if (const QString error = errorMessage(obj); !error.isEmpty()) {
                 return error;
             }
             return toolIsError(obj) ? QString() : u"isError is not set"_s;
         }},
        {u"Call unknown tool (JSON-RPC error)"_s,
         toolCall(u"does_not_exist"_s),
         [](const QJsonObject &obj) {
             return obj.contains("error"_L1) ? QString() : u"Error response expected"_s;
         }},
        {u"Call slow with short timeout (cancelled)"_s,
         [this]() {
             mManager->setRequestTimeout(shortRequestTimeout);
             const qint64 id = mManager->callTool(u"slow"_s, QJsonObject{{"milliseconds"_L1, 3000}});
             mManager->setRequestTimeout(defaultRequestTimeout);
             return id;
         },
         [](const QJsonObject &obj) {
             return obj.value("error"_L1).toObject().value("code"_L1).toInt() == -32001 ? QString() : u"Timeout error expected"_s;
         }},
        {u"Call slow (500 ms)"_s,
         toolCall(u"slow"_s, QJsonObject{{"milliseconds"_L1, 500}}),
         [](const QJsonObject &obj) {
             if (const QString error = errorMessage(obj); !error.isEmpty()) {
                 return error;
             }
             return toolText(obj) == "Waited 500 ms"_L1 ? QString() : u"Unexpected text: %1"_s.arg(toolText(obj));
         }},
        {u"List prompts"_s,
         [this]() {
             return mManager->executeAction(MethodType::ListPrompts);
         },
         [](const QJsonObject &obj) {
             if (const QString error = errorMessage(obj); !error.isEmpty()) {
                 return error;
             }
             return names(obj, u"prompts"_s) == QStringList{u"greeting"_s} ? QString() : u"Prompt \"greeting\" expected"_s;
         }},
        {u"List resource templates"_s,
         [this]() {
             return mManager->executeAction(MethodType::ResourceTemplates);
         },
         [](const QJsonObject &obj) {
             if (const QString error = errorMessage(obj); !error.isEmpty()) {
                 return error;
             }
             return names(obj, u"resourceTemplates"_s) == QStringList{u"file"_s} ? QString() : u"Resource template \"file\" expected"_s;
         }},
    };
}

void MainWidget::runAllChecks()
{
    if (mCurrentCheck >= 0) {
        return;
    }
    if (!mManager || !mManager->isInitialized()) {
        mRunChecksWhenInitialized = true;
        connectToServer();
        updateButtons();
        return;
    }
    log(u"===== Run %1 checks ====="_s.arg(mChecks.count()));
    mFailureCount = 0;
    mCurrentCheck = 0;
    updateButtons();
    runNextCheck();
}

void MainWidget::runNextCheck()
{
    if (mCurrentCheck >= mChecks.count()) {
        finishChecks();
        return;
    }
    mCurrentRequestId = mChecks.at(mCurrentCheck).run();
    if (mCurrentRequestId < 0) {
        checkFinished(u"Request not sent"_s);
        return;
    }
    mCheckTimer->start();
}

void MainWidget::checkFinished(const QString &errorMessage)
{
    if (mCurrentCheck < 0) {
        return;
    }
    mCheckTimer->stop();
    const QString &name = mChecks.at(mCurrentCheck).name;
    if (errorMessage.isEmpty()) {
        log(u"PASS: %1"_s.arg(name));
    } else {
        ++mFailureCount;
        log(u"FAIL: %1: %2"_s.arg(name, errorMessage));
    }
    // Print in stdout: result is visible when log goes to journald (--autorun in script)
    QTextStream(stdout) << (errorMessage.isEmpty() ? u"PASS: %1"_s.arg(name) : u"FAIL: %1: %2"_s.arg(name, errorMessage)) << Qt::endl;
    mCurrentRequestId = -1;
    ++mCurrentCheck;
    if (!mManager) {
        // Client finished: other checks can't run
        mFailureCount += mChecks.count() - mCurrentCheck;
        finishChecks();
        return;
    }
    // Don't run next request in slot of current response
    QTimer::singleShot(0, this, &MainWidget::runNextCheck);
}

void MainWidget::finishChecks()
{
    mCurrentCheck = -1;
    const QString summary = mFailureCount == 0 ? u"===== All checks passed ====="_s : u"===== %1 check(s) failed ====="_s.arg(mFailureCount);
    log(summary);
    QTextStream(stdout) << summary << Qt::endl;
    updateButtons();
    Q_EMIT checksFinished(mFailureCount);
}

#include "moc_mainwidget.cpp"
