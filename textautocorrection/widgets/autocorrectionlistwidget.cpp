/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionlistwidget.h"

#include <QKeyEvent>

using namespace TextAutoCorrectionWidgets;

AutoCorrectionListWidget::AutoCorrectionListWidget(QWidget *parent)
    : QListWidget(parent)
{
}

AutoCorrectionListWidget::~AutoCorrectionListWidget() = default;

void AutoCorrectionListWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        Q_EMIT deleteSelectedItems();
    }
    QListWidget::keyPressEvent(event);
}

#include "moc_autocorrectionlistwidget.cpp"
