/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QHash>
#include <QPixmap>
#include <QSet>
#include <QStyledItemDelegate>
class QNetworkAccessManager;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT McpRegistryServerListViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit McpRegistryServerListViewDelegate(QObject *parent = nullptr);
    ~McpRegistryServerListViewDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

Q_SIGNALS:
    void iconLoaded();

private:
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT QPixmap serverIcon(const QString &url) const;
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void downloadIcon(const QString &url) const;
    QNetworkAccessManager *const mNetworkAccessManager;
    // Null pixmap when the download failed: avoids downloading it again
    mutable QHash<QString, QPixmap> mIconCache;
    mutable QSet<QString> mPendingDownloads;
};
}
