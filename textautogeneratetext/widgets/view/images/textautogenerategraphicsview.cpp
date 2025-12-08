/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerategraphicsview.h"
#include <QScopedValueRollback>
#include <QWheelEvent>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
constexpr qreal defaultMinimumZoomScale = (qreal)0.1;
constexpr qreal defaultMaximumZoomScale = (qreal)10.0;

qreal fitToViewZoomScale(QSize imageSize, QSize widgetSize)
{
    if (imageSize.width() > widgetSize.width() || imageSize.height() > widgetSize.height()) {
        // Make sure it fits, we care only about the first two decimal points, so round to the smaller value
        const qreal hZoom = (qreal)widgetSize.width() / imageSize.width();
        const qreal vZoom = (qreal)widgetSize.height() / imageSize.height();
        return std::max((int)(std::min(hZoom, vZoom) * 100) / 100.0, defaultMinimumZoomScale);
    }
    return 1.0;
}
}
TextAutoGenerateGraphicsView::TextAutoGenerateGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , mMinimumZoom(defaultMinimumZoomScale)
    , mMaximumZoom(defaultMaximumZoomScale)
{
    setDragMode(QGraphicsView::ScrollHandDrag);

    auto scene = new QGraphicsScene(this);
    setScene(scene);
}

TextAutoGenerateGraphicsView::~TextAutoGenerateGraphicsView() = default;

void TextAutoGenerateGraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() == Qt::ControlModifier) {
        const int y = e->angleDelta().y();
        if (y < 0) {
            zoomOut(e->position());
        } else if (y > 0) {
            zoomIn(e->position());
        } // else: y == 0 => horizontal scroll => do not handle
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

void TextAutoGenerateGraphicsView::zoomIn(QPointF centerPos)
{
    setZoom(zoom() * 1.1, centerPos);
}

void TextAutoGenerateGraphicsView::zoomOut(QPointF centerPos)
{
    setZoom(zoom() * 0.9, centerPos);
}

qreal TextAutoGenerateGraphicsView::zoom() const
{
    return transform().m11();
}

qreal TextAutoGenerateGraphicsView::minimumZoom() const
{
    return mMinimumZoom;
}

qreal TextAutoGenerateGraphicsView::maximumZoom() const
{
    return mMaximumZoom;
}

void TextAutoGenerateGraphicsView::setZoom(qreal zoom, QPointF centerPos)
{
    // clamp value
    zoom = qBound(minimumZoom(), zoom, maximumZoom());

    if (qFuzzyCompare(this->zoom(), zoom)) {
        return;
    }

    if (mIsUpdatingZoom) {
        return;
    }

    QScopedValueRollback<bool> guard(mIsUpdatingZoom, true);

    QPointF targetScenePos;
    if (!centerPos.isNull()) {
        targetScenePos = mapToScene(centerPos.toPoint());
    } else {
        targetScenePos = sceneRect().center();
    }

    ViewportAnchor oldAnchor = this->transformationAnchor();
    setTransformationAnchor(QGraphicsView::NoAnchor);

    QTransform matrix;
    matrix.translate(targetScenePos.x(), targetScenePos.y()).scale(zoom, zoom).translate(-targetScenePos.x(), -targetScenePos.y());
    setTransform(matrix);

    setTransformationAnchor(oldAnchor);
    Q_EMIT zoomChanged(zoom);
}

void TextAutoGenerateGraphicsView::fitToView()
{
#if 0
    setZoom(fitToViewZoomScale(originalImageSize(), size()));
    centerOn(mGraphicsPixmapItem);
#endif
}

#include "moc_textautogenerategraphicsview.cpp"
