/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QGraphicsPixmapItem>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    explicit TextAutoGenerateGraphicsPixmapItem(QGraphicsItem *parent = nullptr);
    ~TextAutoGenerateGraphicsPixmapItem() override;
    void setImagePath(const QString &path);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString mImagePath;
    QPointF mDragStartPosition;
};
}
