/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginstreewidgetdelegate.h"
#include "configurepluginswidget.h"
#include <QApplication>
#include <QPainter>
using namespace TextAddonsWidgets;
ConfigurePluginsTreeWidgetDelegate::ConfigurePluginsTreeWidgetDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

ConfigurePluginsTreeWidgetDelegate::~ConfigurePluginsTreeWidgetDelegate() = default;

void ConfigurePluginsTreeWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    // Get the text and split it into two lines
    const QString text = index.data(Qt::DisplayRole).toString();
    if (text.isEmpty()) {
        return;
    }

    const QString description = index.data(TextAddonsWidgets::ConfigurePluginsWidget::PluginItemData::Description).toString();
    if (description.isEmpty()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    QStyleOptionViewItem opt(option);
    opt.showDecorationSelected = true;
    initStyleOption(&opt, index);
    opt.text.clear();
    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

    painter->save();

    // Set the painter font
    painter->setFont(option.font);

    // Calculate the text rectangles
    const QFontMetrics fontMetrics(option.font);
    const QRect rect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemText, &opt, opt.widget);

    // Draw the two lines
    const int alignment = Qt::AlignLeft | Qt::AlignVCenter;
    const bool enabled = opt.state & QStyle::State_Enabled;

    QPalette::ColorGroup colorGroup;
    if (enabled) {
        if (!(opt.state & QStyle::State_Active)) {
            colorGroup = QPalette::Inactive;
        } else {
            colorGroup = QPalette::Normal;
        }
    } else {
        colorGroup = QPalette::Disabled;
    }
    opt.palette.setCurrentColorGroup(colorGroup);

    const QPalette::ColorRole colorRole = opt.state & QStyle::State_Selected ? QPalette::HighlightedText : QPalette::Text;

    const QRect line1Rect(rect.left(), rect.top(), rect.width(), fontMetrics.height());
    QApplication::style()->drawItemText(painter, line1Rect, alignment, opt.palette, enabled, text, colorRole);

    QFont f = opt.font;
    f.setItalic(true);
    f.setPointSize(f.pointSize() - 2);
    painter->setFont(f);

    const QRect line2Rect(rect.left(), rect.top() + fontMetrics.height(), rect.width(), fontMetrics.height());
    QApplication::style()->drawItemText(painter, line2Rect, alignment, opt.palette, enabled, description, colorRole);

    painter->restore();
}

QSize ConfigurePluginsTreeWidgetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QFontMetrics fontMetrics(option.font);
    const int height = fontMetrics.height() * 2; // Height for two lines

    const QString description = index.data(TextAddonsWidgets::ConfigurePluginsWidget::PluginItemData::Description).toString();
    int widthDescription = 0;
    if (!description.isEmpty()) {
        QFont f = option.font;
        f.setItalic(true);
        f.setPointSize(f.pointSize() - 2);
        const QFontMetrics italicFont(f);
        widthDescription = italicFont.horizontalAdvance(description);
    }

    const int width = qMax(fontMetrics.horizontalAdvance(index.data(Qt::DisplayRole).toString()), widthDescription);
    return QSize(width, height);
}

#include "moc_configurepluginstreewidgetdelegate.cpp"
