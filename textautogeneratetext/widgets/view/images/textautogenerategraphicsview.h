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

private:
    qreal mMinimumZoom;
    qreal mMaximumZoom;
};
}
