/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QPointer>
#include <QWidget>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerInfo>
class QLineEdit;
class QLabel;
class QPushButton;
class QTimer;
class QNetworkAccessManager;
class QNetworkReply;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class McpRegistryServerListView;
class McpRegistryServerInfoWidget;
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpRegistryServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpRegistryServerWidget(QWidget *parent = nullptr);
    ~AddMcpRegistryServerWidget() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo currentServerInfo() const;

    void loadServers();

Q_SIGNALS:
    void currentServerChanged(const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &info);

protected:
    void showEvent(QShowEvent *event) override;

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void fetchServers(const QString &cursor);
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotServerSelected(const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &info);
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotReplyFinished(QNetworkReply *reply, bool append);
    TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo mCurrentServerInfo;
    QString mNextCursor;
    QLineEdit *const mSearchLineEdit;
    McpRegistryServerListView *const mListView;
    McpRegistryServerInfoWidget *const mInfoWidget;
    QLabel *const mStatusLabel;
    QPushButton *const mLoadMoreButton;
    QTimer *const mSearchTimer;
    QNetworkAccessManager *const mNetworkAccessManager;
    QPointer<QNetworkReply> mReply;
    bool mInitialized = false;
};
}
