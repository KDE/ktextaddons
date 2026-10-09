/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "servermainwidget.h"
#include "mcptestserver.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

ServerMainWidget::ServerMainWidget(const QString &url, QWidget *parent)
    : QWidget{parent}
    , mServer(new McpTestServer(this))
    , mUrl(new QLineEdit(url, this))
    , mStartButton(new QPushButton(u"Start"_s, this))
    , mStopButton(new QPushButton(u"Stop"_s, this))
    , mToggleToolButton(new QPushButton(u"Add/Remove \"reverse\" tool"_s, this))
    , mPingButton(new QPushButton(u"Ping client"_s, this))
    , mLog(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);

    auto urlLayout = new QHBoxLayout;
    urlLayout->addWidget(new QLabel(u"Url:"_s, this));
    urlLayout->addWidget(mUrl);
    urlLayout->addWidget(mStartButton);
    urlLayout->addWidget(mStopButton);
    mainLayout->addLayout(urlLayout);

    auto actionLayout = new QHBoxLayout;
    actionLayout->addWidget(mToggleToolButton);
    actionLayout->addWidget(mPingButton);
    actionLayout->addStretch();
    auto clearButton = new QPushButton(u"Clear log"_s, this);
    actionLayout->addWidget(clearButton);
    mainLayout->addLayout(actionLayout);

    mLog->setReadOnly(true);
    mainLayout->addWidget(mLog);

    connect(mStartButton, &QPushButton::clicked, this, &ServerMainWidget::startServer);
    connect(mStopButton, &QPushButton::clicked, mServer, &McpTestServer::stop);
    connect(mToggleToolButton, &QPushButton::clicked, mServer, &McpTestServer::toggleExtraTool);
    connect(mPingButton, &QPushButton::clicked, mServer, &McpTestServer::pingClient);
    connect(clearButton, &QPushButton::clicked, mLog, &QPlainTextEdit::clear);
    connect(mServer, &McpTestServer::logMessage, mLog, &QPlainTextEdit::appendPlainText);
    connect(mServer, &McpTestServer::runningChanged, this, &ServerMainWidget::updateButtons);
    updateButtons(false);
}

ServerMainWidget::~ServerMainWidget() = default;

void ServerMainWidget::startServer()
{
    mServer->start(QUrl(mUrl->text().trimmed()));
}

void ServerMainWidget::updateButtons(bool running)
{
    mUrl->setEnabled(!running);
    mStartButton->setEnabled(!running);
    mStopButton->setEnabled(running);
    mToggleToolButton->setEnabled(running);
    mPingButton->setEnabled(running);
}

#include "moc_servermainwidget.cpp"
