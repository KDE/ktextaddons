/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagerlistviewdelegate.h"
#include "core/models/textautogeneratetextinstancemodel.h"
#include <QApplication>
#include <QPainter>

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerListViewDelegate::TextAutoGenerateTextInstancesManagerListViewDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

TextAutoGenerateTextInstancesManagerListViewDelegate::~TextAutoGenerateTextInstancesManagerListViewDelegate() = default;

void TextAutoGenerateTextInstancesManagerListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    // Get the text and split it into two lines
    const QString text = index.data(Qt::DisplayRole).toString();
    if (text.isEmpty()) {
        return;
    }

    const QString pluginName = index.data(TextAutoGenerateTextInstanceModel::PluginName).toString();
    if (pluginName.isEmpty()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    QStyleOptionViewItem opt(option);
    opt.showDecorationSelected = true;
    QApplication::style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);

    painter->save();

    // Set the painter font
    painter->setFont(option.font);

    // Calculate the text rectangles
    QFontMetrics fontMetrics(option.font);
    const QRect rect = option.rect;

    // Draw the two lines
    painter->setPen(option.palette.text().color());
    const QRect line1Rect(rect.left() + 5, rect.top(), rect.width(), fontMetrics.height());
    painter->drawText(line1Rect, Qt::AlignLeft | Qt::AlignVCenter, text);
    if (!pluginName.isEmpty()) {
        QFont f = option.font;
        f.setItalic(true);
        f.setPointSize(f.pointSize() - 2);
        painter->setFont(f);
        const QRect line2Rect(rect.left() + 5, rect.top() + fontMetrics.height(), rect.width(), fontMetrics.height());
        painter->drawText(line2Rect, Qt::AlignLeft | Qt::AlignVCenter, pluginName);
    }
    painter->restore();
}

QSize TextAutoGenerateTextInstancesManagerListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFontMetrics fontMetrics(option.font);
    const int height = fontMetrics.height() * 2; // Height for two lines

    const QString pluginName = index.data(TextAutoGenerateTextInstanceModel::PluginName).toString();
    int widthDescription = 0;
    if (!pluginName.isEmpty()) {
        QFont f = option.font;
        f.setItalic(true);
        f.setPointSize(f.pointSize() - 2);
        widthDescription = fontMetrics.horizontalAdvance(pluginName);
    }

    const int width = qMax(fontMetrics.horizontalAdvance(index.data(Qt::DisplayRole).toString()), widthDescription);
    return QSize(width, height);
}

#include "moc_textautogeneratetextinstancesmanagerlistviewdelegate.cpp"
