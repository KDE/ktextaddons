/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textutils_export.h"
#include <KColorScheme>
#include <QObject>

namespace TextUtils
{
/*!
 * \brief The TextUtilsColorsAndMessageViewStyle class
 * \author Laurent Montel <montel@kde.org>
 * \class TextUtilsColorsAndMessageViewStyle
 * \inheaderfile TextUtils/TextUtilsColorsAndMessageViewStyle
 * \inmodule TextUtils
 */
class TEXTUTILS_EXPORT TextUtilsColorsAndMessageViewStyle : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Returns the singleton instance of TextUtilsColorsAndMessageViewStyle
     * \return Reference to the singleton instance
     */
    static TextUtilsColorsAndMessageViewStyle &self();
    /*!
     * \brief Constructs a new TextUtilsColorsAndMessageViewStyle instance
     */
    TextUtilsColorsAndMessageViewStyle();

    /*!
     * \brief Returns the view color scheme
     * \return KColorScheme for view
     */
    [[nodiscard]] KColorScheme schemeView() const;

    /*!
     * \brief Returns the window color scheme
     * \return KColorScheme for window
     */
    [[nodiscard]] KColorScheme schemeWindow() const;

Q_SIGNALS:
    /*!
     * \brief Emitted when colors need to be updated
     */
    void needToUpdateColors();
    /*!
     * \brief Emitted when message style needs to be updated
     */
    void needUpdateMessageStyle();
    /*!
     * \brief Emitted when font size needs to be updated
     */
    void needUpdateFontSize();

protected:
    /*!
     * \brief Handles events for the color scheme update
     * \param obj The object that received the event
     * \param event The event
     * \return true if the event was handled
     */
    [[nodiscard]] bool eventFilter(QObject *obj, QEvent *event) override;

private:
    TEXTUTILS_NO_EXPORT void regenerateColorScheme();
    KColorScheme mSchemeView;
    KColorScheme mSchemeWindow;
};
}
