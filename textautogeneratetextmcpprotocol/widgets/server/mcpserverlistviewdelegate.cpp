/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverlistviewdelegate.h"
#include <QApplication>
#include <QPainter>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
using namespace TextAutoGenerateTextMcpProtocolWidgets;

McpServerListViewDelegate::McpServerListViewDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

McpServerListViewDelegate::~McpServerListViewDelegate() = default;

namespace
{
QFont descriptionFont(const QFont &font)
{
    QFont f = font;
    f.setItalic(true);
    if (f.pointSizeF() > 0) {
        f.setPointSizeF(qMax(1.0, f.pointSizeF() - 2));
    } else if (f.pixelSize() > 0) {
        f.setPixelSize(qMax(1, f.pixelSize() - 2));
    }
    return f;
}

QStyle *widgetStyle(const QStyleOptionViewItem &option)
{
    return option.widget ? option.widget->style() : QApplication::style();
}
}

void McpServerListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    const QString text = index.data(Qt::DisplayRole).toString();
    const QString serverTypeName = index.data(TextAutoGenerateTextMcpProtocolCore::McpServerModel::ServerType).toString();
    if (text.isEmpty() || serverTypeName.isEmpty()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    QStyle *style = widgetStyle(opt);

    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &opt, opt.widget);
    opt.text.clear();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

    const int textMargin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, nullptr, opt.widget) + 1;
    textRect.adjust(textMargin, 0, -textMargin, 0);

    const QFont descFont = descriptionFont(opt.font);
    const QFontMetrics fontMetrics(opt.font);
    const QFontMetrics descFontMetrics(descFont);
    const int top = textRect.top() + qMax(0, (textRect.height() - fontMetrics.height() - descFontMetrics.height()) / 2);

    QPalette::ColorGroup colorGroup = QPalette::Normal;
    if (!(opt.state & QStyle::State_Enabled)) {
        colorGroup = QPalette::Disabled;
    } else if (!(opt.state & QStyle::State_Active)) {
        colorGroup = QPalette::Inactive;
    }
    const QPalette::ColorRole colorRole = (opt.state & QStyle::State_Selected) ? QPalette::HighlightedText : QPalette::Text;

    painter->save();
    painter->setPen(opt.palette.color(colorGroup, colorRole));

    painter->setFont(opt.font);
    const QRect line1Rect(textRect.left(), top, textRect.width(), fontMetrics.height());
    painter->drawText(line1Rect, Qt::AlignLeft | Qt::AlignVCenter, fontMetrics.elidedText(text, Qt::ElideRight, line1Rect.width()));

    painter->setFont(descFont);
    const QRect line2Rect(textRect.left(), line1Rect.bottom() + 1, textRect.width(), descFontMetrics.height());
    painter->drawText(line2Rect, Qt::AlignLeft | Qt::AlignVCenter, descFontMetrics.elidedText(serverTypeName, Qt::ElideRight, line2Rect.width()));
    painter->restore();
}

QSize McpServerListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    const QStyle *style = widgetStyle(opt);

    const QFontMetrics fontMetrics(opt.font);
    const QFontMetrics descFontMetrics(descriptionFont(opt.font));
    const QString serverTypeName = index.data(TextAutoGenerateTextMcpProtocolCore::McpServerModel::ServerType).toString();

    const int textMargin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, nullptr, opt.widget) + 1;
    int width = qMax(fontMetrics.horizontalAdvance(index.data(Qt::DisplayRole).toString()),
                     serverTypeName.isEmpty() ? 0 : descFontMetrics.horizontalAdvance(serverTypeName));
    width += 2 * textMargin;
    if (opt.features & QStyleOptionViewItem::HasCheckIndicator) {
        width += style->subElementRect(QStyle::SE_ItemViewItemCheckIndicator, &opt, opt.widget).width() + 2 * textMargin;
    }
    const int height = fontMetrics.height() + (serverTypeName.isEmpty() ? 0 : descFontMetrics.height());
    return QSize(width, height).expandedTo(QStyledItemDelegate::sizeHint(option, index));
}

#include "moc_mcpserverlistviewdelegate.cpp"
