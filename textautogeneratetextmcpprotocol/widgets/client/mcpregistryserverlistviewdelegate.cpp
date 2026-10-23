/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpregistryserverlistviewdelegate.h"
#include <QApplication>
#include <QIcon>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPainter>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerModel>
using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;

McpRegistryServerListViewDelegate::McpRegistryServerListViewDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
}

McpRegistryServerListViewDelegate::~McpRegistryServerListViewDelegate() = default;

namespace
{
QFont nameFont(const QFont &font)
{
    QFont f = font;
    f.setBold(true);
    return f;
}

QFont descriptionFont(const QFont &font)
{
    QFont f = font;
    if (f.pointSizeF() > 0) {
        f.setPointSizeF(qMax(1.0, f.pointSizeF() - 1));
    } else if (f.pixelSize() > 0) {
        f.setPixelSize(qMax(1, f.pixelSize() - 1));
    }
    return f;
}

QStyle *widgetStyle(const QStyleOptionViewItem &option)
{
    return option.widget ? option.widget->style() : QApplication::style();
}

int iconSize(const QStyleOptionViewItem &option)
{
    return widgetStyle(option)->pixelMetric(QStyle::PM_ListViewIconSize, nullptr, option.widget);
}

int iconSpacing(const QStyleOptionViewItem &option)
{
    // Some styles return -1 for layout spacing
    return qMax(6, widgetStyle(option)->pixelMetric(QStyle::PM_LayoutHorizontalSpacing, nullptr, option.widget));
}
}

QPixmap McpRegistryServerListViewDelegate::serverIcon(const QString &url) const
{
    if (url.isEmpty()) {
        return {};
    }
    const auto it = mIconCache.constFind(url);
    if (it != mIconCache.cend()) {
        return *it;
    }
    downloadIcon(url);
    return {};
}

void McpRegistryServerListViewDelegate::downloadIcon(const QString &url) const
{
    if (mPendingDownloads.contains(url)) {
        return;
    }
    mPendingDownloads.insert(url);
    QNetworkReply *reply = mNetworkAccessManager->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, this, [this, reply, url]() {
        reply->deleteLater();
        mPendingDownloads.remove(url);
        QPixmap pixmap;
        if (reply->error() == QNetworkReply::NoError) {
            pixmap.loadFromData(reply->readAll());
        }
        mIconCache.insert(url, pixmap);
        if (!pixmap.isNull()) {
            Q_EMIT const_cast<McpRegistryServerListViewDelegate *>(this)->iconLoaded();
        }
    });
}

void McpRegistryServerListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    const QStyle *style = widgetStyle(opt);

    const QString text = opt.text;
    const QString description = index.data(TextAutoGenerateTextMcpProtocolCore::McpRegistryServerModel::Description).toString();

    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &opt, opt.widget);
    opt.text.clear();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

    const int textMargin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, nullptr, opt.widget) + 1;
    textRect.adjust(textMargin, 0, -textMargin, 0);

    const int size = iconSize(opt);
    const QRect iconRect(textRect.left(), textRect.top() + (textRect.height() - size) / 2, size, size);
    const QString iconUrl = index.data(TextAutoGenerateTextMcpProtocolCore::McpRegistryServerModel::IconUrl).toString();
    const QPixmap pixmap = serverIcon(iconUrl);
    if (iconUrl.isEmpty() || pixmap.isNull()) {
        const QIcon icon(QIcon::fromTheme(u"network-server"_s));
        const QPixmap pix = icon.pixmap(iconRect.size() * painter->device()->devicePixelRatioF());
        const QRect targetRect = QStyle::alignedRect(opt.direction, Qt::AlignCenter, pix.deviceIndependentSize().toSize(), iconRect);
        painter->drawPixmap(targetRect, pix);
    } else {
        const QPixmap scaled = pixmap.scaled(iconRect.size() * painter->device()->devicePixelRatioF(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        const QRect targetRect = QStyle::alignedRect(opt.direction, Qt::AlignCenter, scaled.deviceIndependentSize().toSize(), iconRect);
        painter->drawPixmap(targetRect, scaled);
    }
    textRect.setLeft(iconRect.right() + 1 + iconSpacing(opt));

    const QFont titleFont = nameFont(opt.font);
    const QFont descFont = descriptionFont(opt.font);
    const QFontMetrics fontMetrics(titleFont);
    const QFontMetrics descFontMetrics(descFont);
    const int contentHeight = fontMetrics.height() + (description.isEmpty() ? 0 : descFontMetrics.height());
    const int top = textRect.top() + qMax(0, (textRect.height() - contentHeight) / 2);

    QPalette::ColorGroup colorGroup = QPalette::Normal;
    if (!(opt.state & QStyle::State_Enabled)) {
        colorGroup = QPalette::Disabled;
    } else if (!(opt.state & QStyle::State_Active)) {
        colorGroup = QPalette::Inactive;
    }
    const bool selected = opt.state & QStyle::State_Selected;

    painter->save();
    painter->setPen(opt.palette.color(colorGroup, selected ? QPalette::HighlightedText : QPalette::Text));
    painter->setFont(titleFont);
    const QRect line1Rect(textRect.left(), top, textRect.width(), fontMetrics.height());
    painter->drawText(line1Rect, Qt::AlignLeft | Qt::AlignVCenter, fontMetrics.elidedText(text, Qt::ElideRight, line1Rect.width()));

    if (!description.isEmpty()) {
        const QColor descColor = opt.palette.color(colorGroup, selected ? QPalette::HighlightedText : QPalette::PlaceholderText);
        painter->setPen(descColor);
        painter->setFont(descFont);
        const QRect line2Rect(textRect.left(), line1Rect.bottom() + 1, textRect.width(), descFontMetrics.height());
        painter->drawText(line2Rect, Qt::AlignLeft | Qt::AlignVCenter, descFontMetrics.elidedText(description, Qt::ElideRight, line2Rect.width()));
    }
    painter->restore();
}

QSize McpRegistryServerListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    const QStyle *style = widgetStyle(opt);

    const QFontMetrics fontMetrics(nameFont(opt.font));
    const QFontMetrics descFontMetrics(descriptionFont(opt.font));
    const QString description = index.data(TextAutoGenerateTextMcpProtocolCore::McpRegistryServerModel::Description).toString();

    const int textMargin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, nullptr, opt.widget) + 1;
    const int size = iconSize(opt);
    // Description can be long: let the view elide it instead of widening the list
    const int width = size + iconSpacing(opt) + fontMetrics.horizontalAdvance(opt.text) + 2 * textMargin;
    const int verticalMargin = style->pixelMetric(QStyle::PM_FocusFrameVMargin, nullptr, opt.widget) + 2;
    const int height = qMax(size, fontMetrics.height() + (description.isEmpty() ? 0 : descFontMetrics.height())) + 2 * verticalMargin;
    return QSize(width, height).expandedTo(QStyledItemDelegate::sizeHint(option, index));
}

#include "moc_mcpregistryserverlistviewdelegate.cpp"
