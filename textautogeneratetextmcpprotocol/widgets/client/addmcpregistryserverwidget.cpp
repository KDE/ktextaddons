/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpregistryserverwidget.h"
#include "client/mcpregistryserverinfowidget.h"
#include "client/mcpregistryserverlistview.h"
#include "textautogeneratetextmcpprotocol_widgets_debug.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QSplitter>
#include <QTimer>
#include <QUrlQuery>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerModel>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace TextAutoGenerateTextMcpProtocolCore;
using namespace Qt::Literals::StringLiterals;
namespace
{
constexpr int pageSize = 50;
}

AddMcpRegistryServerWidget::AddMcpRegistryServerWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mListView(new McpRegistryServerListView(this))
    , mInfoWidget(new McpRegistryServerInfoWidget(this))
    , mStatusLabel(new QLabel(this))
    , mLoadMoreButton(new QPushButton(i18nc("@action:button", "Load More"), this))
    , mSearchTimer(new QTimer(this))
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search in MCP registry…"));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mainLayout->addWidget(mSearchLineEdit);

    auto splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setObjectName(u"splitter"_s);
    splitter->setChildrenCollapsible(false);
    mainLayout->addWidget(splitter, 1);

    mListView->setObjectName(u"mListView"_s);
    splitter->addWidget(mListView);

    mInfoWidget->setObjectName(u"mInfoWidget"_s);
    splitter->addWidget(mInfoWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    auto bottomLayout = new QHBoxLayout;
    bottomLayout->setObjectName(u"bottomLayout"_s);
    bottomLayout->setContentsMargins(QMargins{});
    mainLayout->addLayout(bottomLayout);

    mStatusLabel->setObjectName(u"mStatusLabel"_s);
    mStatusLabel->setTextFormat(Qt::PlainText);
    bottomLayout->addWidget(mStatusLabel, 1);

    mLoadMoreButton->setObjectName(u"mLoadMoreButton"_s);
    mLoadMoreButton->setEnabled(false);
    bottomLayout->addWidget(mLoadMoreButton);
    connect(mLoadMoreButton, &QPushButton::clicked, this, [this]() {
        fetchServers(mNextCursor);
    });

    mSearchTimer->setSingleShot(true);
    mSearchTimer->setInterval(500);
    connect(mSearchTimer, &QTimer::timeout, this, &AddMcpRegistryServerWidget::loadServers);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mSearchTimer, qOverload<>(&QTimer::start));

    connect(mListView, &McpRegistryServerListView::serverSelected, this, &AddMcpRegistryServerWidget::slotServerSelected);
}

AddMcpRegistryServerWidget::~AddMcpRegistryServerWidget()
{
    if (mReply) {
        mReply->abort();
    }
}

McpRegistryServerInfo AddMcpRegistryServerWidget::currentServerInfo() const
{
    return mCurrentServerInfo;
}

void AddMcpRegistryServerWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    if (!mInitialized) {
        mInitialized = true;
        loadServers();
    }
}

void AddMcpRegistryServerWidget::loadServers()
{
    mListView->registryServerModel()->clear();
    fetchServers({});
}

void AddMcpRegistryServerWidget::fetchServers(const QString &cursor)
{
    if (mReply) {
        mReply->abort();
    }
    QUrl url(u"https://registry.modelcontextprotocol.io/v0/servers"_s);
    QUrlQuery query;
    query.addQueryItem(u"limit"_s, QString::number(pageSize));
    query.addQueryItem(u"version"_s, u"latest"_s);
    if (const QString searchText = mSearchLineEdit->text().trimmed(); !searchText.isEmpty()) {
        query.addQueryItem(u"search"_s, searchText);
    }
    if (!cursor.isEmpty()) {
        query.addQueryItem(u"cursor"_s, cursor);
    }
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Accept", "application/json");
    mLoadMoreButton->setEnabled(false);
    mStatusLabel->setText(i18n("Loading…"));
    QNetworkReply *reply = mNetworkAccessManager->get(request);
    mReply = reply;
    const bool append = !cursor.isEmpty();
    connect(reply, &QNetworkReply::finished, this, [this, reply, append]() {
        slotReplyFinished(reply, append);
    });
}

void AddMcpRegistryServerWidget::slotReplyFinished(QNetworkReply *reply, bool append)
{
    reply->deleteLater();
    if (reply->error() == QNetworkReply::OperationCanceledError) {
        return;
    }
    if (reply->error() != QNetworkReply::NoError) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Failed to fetch mcp registry servers:" << reply->errorString();
        mStatusLabel->setText(i18n("Impossible to load servers: %1", reply->errorString()));
        mLoadMoreButton->setEnabled(!mNextCursor.isEmpty() && append);
        return;
    }
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "Invalid mcp registry answer:" << parseError.errorString();
        mStatusLabel->setText(i18n("Invalid answer from MCP registry."));
        return;
    }
    const QList<McpRegistryServerInfo> servers = McpRegistryServerInfo::parseServerList(doc.object(), mNextCursor);
    auto model = mListView->registryServerModel();
    if (append) {
        model->appendServers(servers);
    } else {
        model->setServers(servers);
    }
    mStatusLabel->setText(i18np("1 server", "%1 servers", model->rowCount()));
    mLoadMoreButton->setEnabled(!mNextCursor.isEmpty());
}

void AddMcpRegistryServerWidget::slotServerSelected(const McpRegistryServerInfo &info)
{
    mCurrentServerInfo = info;
    mInfoWidget->setServerInfo(info);
    Q_EMIT currentServerChanged(info);
}

#include "moc_addmcpregistryserverwidget.cpp"
