/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <KMessageWidget>
#include <QWidget>
class QTimer;
namespace TextAddonsWidgets
{
/**
 * @short A widget that displays messages in the top-left corner.
 *
 * This is a widget with thin border and rounded corners that displays a given
 * text along as an icon. It's meant to be used for displaying messages to the
 * user by placing this above other widgets.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT TextMessageWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextMessageWidget(QWidget *parent = nullptr);

    /*!
     */
    void showMessage(const QString &message,
                     const QString &details = QString(),
                     KMessageWidget::MessageType type = KMessageWidget::MessageType::Positive,
                     int durationMs = 4000);

    /*!
     * \brief setTextFormat
     * \param textFormat
     */
    void setTextFormat(Qt::TextFormat textFormat);

private:
    KMessageWidget *const mMessageWidget;
    QTimer *const mAutoHideTimer;
};
}
