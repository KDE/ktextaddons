/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogenerateflowlayout.h"

#include <QStyle>
#include <QWidget>
using namespace TextAutoGenerateText;
static int smartSpacing(QObject *parent, QStyle::PixelMetric pm)
{
    if (!parent) {
        return -1;
    } else if (parent->isWidgetType()) {
        auto pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    } else {
        return static_cast<QLayout *>(parent)->spacing();
    }
}

TextAutoGenerateFlowLayout::TextAutoGenerateFlowLayout(QWidget *parent)
    : QLayout(parent)
{
}

TextAutoGenerateFlowLayout::~TextAutoGenerateFlowLayout()
{
    clear();
}

int TextAutoGenerateFlowLayout::horizontalSpacing() const
{
    if (mHorizontalSpacing >= 0) {
        return mHorizontalSpacing;
    } else {
        return smartSpacing(parent(), QStyle::PM_LayoutHorizontalSpacing);
    }
}

void TextAutoGenerateFlowLayout::setHorizontalSpacing(int horizontalSpacing)
{
    if (mHorizontalSpacing != horizontalSpacing) {
        mHorizontalSpacing = horizontalSpacing;
        invalidate();
    }
}

int TextAutoGenerateFlowLayout::verticalSpacing() const
{
    if (mVerticalSpacing >= 0) {
        return mVerticalSpacing;
    } else {
        return smartSpacing(parent(), QStyle::PM_LayoutVerticalSpacing);
    }
}

void TextAutoGenerateFlowLayout::setVerticalSpacing(int verticalSpacing)
{
    if (mVerticalSpacing != verticalSpacing) {
        mVerticalSpacing = verticalSpacing;
        invalidate();
    }
}

QSize TextAutoGenerateFlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize TextAutoGenerateFlowLayout::minimumSize() const
{
    const QMargins margins = contentsMargins();
    QSize size;

    for (const QLayoutItem *item : mItems) {
        size = size.expandedTo(item->minimumSize());
    }

    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    return size;
}

void TextAutoGenerateFlowLayout::addItem(QLayoutItem *item)
{
    Q_ASSERT(!mItems.contains(item));
    mItems.append(item);
    invalidate();
}

QLayoutItem *TextAutoGenerateFlowLayout::itemAt(int index) const
{
    if (index >= 0 && index < mItems.count()) {
        return mItems[index];
    }

    return nullptr;
}

QLayoutItem *TextAutoGenerateFlowLayout::takeAt(int index)
{
    if (index >= 0 && index < mItems.count()) {
        auto *it = mItems.takeAt(index);
        invalidate();
        return it;
    }

    return nullptr;
}

int TextAutoGenerateFlowLayout::count() const
{
    return mItems.count();
}

Qt::Orientations TextAutoGenerateFlowLayout::expandingDirections() const
{
    return {};
}

bool TextAutoGenerateFlowLayout::hasHeightForWidth() const
{
    return true;
}

int TextAutoGenerateFlowLayout::heightForWidth(int width) const
{
    return doFlow(QRect(0, 0, width, 0), false);
}

void TextAutoGenerateFlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doFlow(rect, true);
}

void TextAutoGenerateFlowLayout::clear()
{
    while (QLayoutItem *item = takeAt(0)) {
        delete item;
    }
}

void TextAutoGenerateFlowLayout::clearAndDeleteWidgets()
{
    while (QLayoutItem *item = takeAt(0)) {
        item->widget()->deleteLater();
        delete item;
    }
}

int TextAutoGenerateFlowLayout::doFlow(QRect rect, bool effective) const
{
    const QMargins margins = contentsMargins();
    const QRect effectiveRect = rect.adjusted(margins.left(), margins.top(), -margins.right(), -margins.bottom());
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int highest = 0;

    for (QLayoutItem *item : mItems) {
        const QWidget *widget = item->widget();

        if (!widget->isVisibleTo(parentWidget())) {
            continue;
        }

        int hSpacing = horizontalSpacing();
        int vSpacing = verticalSpacing();

        if (hSpacing == -1) {
            hSpacing = widget->style()->layoutSpacing(QSizePolicy::Frame, QSizePolicy::Frame, Qt::Horizontal);
        }

        if (vSpacing == -1) {
            vSpacing = widget->style()->layoutSpacing(QSizePolicy::Frame, QSizePolicy::Frame, Qt::Vertical);
        }

        int widgetXPos = x + item->sizeHint().width() + hSpacing;

        if (widgetXPos - hSpacing > effectiveRect.right() && highest > 0) {
            x = effectiveRect.x();
            y += highest + vSpacing;
            widgetXPos = x + item->sizeHint().width() + hSpacing;
            highest = 0;
        }

        if (effective) {
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
        }

        x = widgetXPos;
        highest = qMax(highest, item->sizeHint().height());
    }

    return y + highest - rect.y() + margins.bottom();
}

#include "moc_textautogenerateflowlayout.cpp"
