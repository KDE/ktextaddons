/*
Gwenview: an image viewer
SPDX-FileCopyrightText: 2007 Aurélien Gâteau <agateau@kde.org>

SPDX-License-Identifier: GPL-2.0-or-later

*/
#pragma once

// Qt
#include <QFrame>
#include <QPointer>

#include "textaddonswidgets_export.h"

class QPropertyAnimation;

namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::SlideContainer
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/SlideContainer
 *
 * This widget is design to contain one child widget, the "content" widget.
 * It will start hidden by default. Calling slideIn() will slide in the content
 * widget from the top border. Calling slideOut() will slide it out.
 */
class TEXTADDONSWIDGETS_EXPORT SlideContainer : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int slideHeight READ slideHeight WRITE setSlideHeight)
public:
    /*!
     * \brief Constructs a SlideContainer widget
     * \param parent The parent widget
     */
    explicit SlideContainer(QWidget *parent = nullptr);

    /*!
     * Returns the content widget
     */
    QWidget *content() const;

    /*!
     * Defines the content widget
     */
    void setContent(QWidget *content);

    /*!
     * Returns the size hint for this widget
     */
    QSize sizeHint() const override;
    /*!
     * Returns the minimum size hint for this widget
     */
    QSize minimumSizeHint() const override;

    /*!
     * Returns the slide height of the content widget
     */
    [[nodiscard]] int slideHeight() const;

    /*!
     * Sets the slide height of the content widget
     * \param height The height to slide to
     */
    Q_INVOKABLE void setSlideHeight(int height);

public Q_SLOTS:
    /*!
     * Slides the content widget in.
     * Calling it multiple times won't cause the animation to be replayed.
     */
    void slideIn();

    /*!
     * Slides the content widget out.
     * Calling it multiple times won't cause the animation to be replayed.
     */
    void slideOut();

Q_SIGNALS:
    /*!\brief Emitted when the slide animation has finished sliding in */
    void slidedIn();
    /*!
     * \brief Emitted when the slide animation has finished sliding out
     */
    void slidedOut();

protected:
    /*!
     * \brief Handles resize events for the slide container
     * \param arg The resize event
     */
    void resizeEvent(QResizeEvent *) override;
    /*!
     * \brief Handles events for the slide container
     * \param obj The object that received the event
     * \param event The event that occurred
     * \return True if the event was handled, false otherwise
     */
    bool eventFilter(QObject *, QEvent *event) override;

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotAnimFinished();
    TEXTADDONSWIDGETS_NO_EXPORT void adjustContentGeometry();

    TEXTADDONSWIDGETS_NO_EXPORT void animTo(int height);
    QPointer<QWidget> mContent;
    QPointer<QPropertyAnimation> mAnim;
    bool mSlidingOut = false;
};
} /* namespace */
