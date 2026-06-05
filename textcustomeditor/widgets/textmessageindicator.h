/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QTimer;
class KMessageWidget;
namespace TextCustomEditor
{
/**
 * @short A widget that displays messages in the top-left corner.
 *
 * This is a widget with thin border and rounded corners that displays a given
 * text along as an icon. It's meant to be used for displaying messages to the
 * user by placing this above other widgets.
 * \author Laurent Montel <montel@kde.org>
 */
class TextMessageIndicator : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextMessageIndicator(QWidget *parent = nullptr);

    enum Icon : uint8_t {
        None = 0,
        Info,
        Warning,
        Error,
    };

    /*!
     */
    void display(const QString &message, const QString &details = QString(), Icon icon = None, int durationMs = 4000);

private:
    KMessageWidget *const mMessageWidget;
    QTimer *const mAutoHideTimer;
};
}
