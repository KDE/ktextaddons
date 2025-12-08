/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QGraphicsView>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateGraphicsView(QWidget *parent = nullptr);
    ~TextAutoGenerateGraphicsView() override;

    [[nodiscard]] qreal zoom() const;
    void setZoom(qreal zoom, QPointF centerPos = {});
    void zoomIn(QPointF centerPos);
    void zoomOut(QPointF centerPos);

    [[nodiscard]] qreal minimumZoom() const;
    [[nodiscard]] qreal maximumZoom() const;

Q_SIGNALS:
    void zoomChanged(qreal zoom);
    void minimumZoomChanged(qreal zoom);
    void maximumZoomChanged(qreal zoom);

protected:
    void wheelEvent(QWheelEvent *e) override;

private:
    QGraphicsProxyWidget *mGraphicsProxyWidget = nullptr;
    qreal mMinimumZoom;
    qreal mMaximumZoom;
    bool mIsUpdatingZoom = false;
};
}
