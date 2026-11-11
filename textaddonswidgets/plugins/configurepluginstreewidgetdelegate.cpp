/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginstreewidgetdelegate.h"
#include "configurepluginswidget.h"
#include <QApplication>
#include <QFontDatabase>
#include <QPainter>
using namespace TextAddonsWidgets;

inline constexpr auto DescriptionRole = TextAddonsWidgets::ConfigurePluginsWidget::PluginItemData::Description;

static inline QFont descriptionFont(QFont font = {})
{
    // Don't go smaller than the smallest readable font or smaller than the
    // current font if already smaller than the smallest readable font.
    const auto smallFont = QFontDatabase::systemFont(QFontDatabase::SmallestReadableFont);
    const auto smallSize = std::min(smallFont.pointSizeF(), font.pointSizeF());
    font.setPointSizeF(std::max(smallSize, font.pointSizeF() - 2));
    font.setItalic(true);
    return font;
}

static inline QStyle *widgetStyle(const QWidget *widget)
{
    return widget ? widget->style() : QApplication::style();
}

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

    // Start like QStyledItemDelegate
    auto opt = option;
    initStyleOption(&opt, index);
    const auto view = option.widget;
    const auto viewStyle = widgetStyle(view);

    const auto description = displayText(index.data(DescriptionRole), opt.locale);
    if (description.isEmpty()) {
        // End like QStyledItemDelegate if no description
        viewStyle->drawControl(QStyle::CE_ItemViewItem, &opt, painter, view);
        return;
    }

    // QCommonStyle subtracts this from the available width when drawing view item text.
    const auto textMargin = viewStyle->pixelMetric(QStyle::PM_FocusFrameHMargin, &opt, view) + 1;
    // Get area available for text decided by the style. It may be larger than
    // the actual area used by the text.
    const auto availableRect = viewStyle->subElementRect(QStyle::SE_ItemViewItemText, &opt, view).adjusted(textMargin, 0, -textMargin, 0);
    const auto textAlignment = viewStyle->visualAlignment(opt.direction, opt.displayAlignment);
    const auto textFlags = textAlignment | opt.textElideMode;
    const auto halign = textAlignment & Qt::AlignHorizontal_Mask;
    const bool enabled = opt.state & QStyle::State_Enabled;

    // Get display bounds
    const auto display = displayText(index.data(Qt::DisplayRole), opt.locale);
    auto displayRect = viewStyle->itemTextRect(opt.fontMetrics, availableRect, textFlags, enabled, display);

    // Get description bounds
    auto descriptionRect = viewStyle->itemTextRect(opt.fontMetrics, availableRect, textFlags, enabled, description);
    descriptionRect.moveTop(displayRect.bottom());

    // Get true text areas
    const auto trueTextRect = viewStyle->alignedRect(opt.direction, textAlignment, (displayRect | descriptionRect).size(), availableRect);
    displayRect = viewStyle->alignedRect(opt.direction, halign | Qt::AlignTop, displayRect.size(), trueTextRect);
    descriptionRect = viewStyle->alignedRect(opt.direction, halign | Qt::AlignBottom, descriptionRect.size(), trueTextRect);

    // Draw without text first
    opt.text.clear();
    viewStyle->drawControl(QStyle::CE_ItemViewItem, &opt, painter, view);

    // Get the correct colors
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

    // Draw the text separately because the description needs a different font.
    const auto lineFlags = halign | Qt::AlignVCenter | opt.textElideMode;
    painter->save();
    painter->setFont(opt.font);
    viewStyle->drawItemText(painter, displayRect, lineFlags, opt.palette, enabled, display, colorRole);
    painter->setFont(descriptionFont(opt.font));
    viewStyle->drawItemText(painter, descriptionRect, lineFlags, opt.palette, enabled, description, colorRole);
    painter->restore();
}

void ConfigurePluginsTreeWidgetDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    // QStyledItemDelegate::initStyleOption assumes option is not null.
    QStyledItemDelegate::initStyleOption(option, index);
    const auto description = displayText(index.data(DescriptionRole), option->locale);
    if (!description.isEmpty()) {
        // The description is supposed to use a smaller font than the display text,
        // so it can't really go in the same string for painting. However, it's
        // easier to make all of the other behaviors work correctly this way.
        option->text = option->text % QChar::LineSeparator % description;
    }
}

#include "moc_configurepluginstreewidgetdelegate.cpp"
