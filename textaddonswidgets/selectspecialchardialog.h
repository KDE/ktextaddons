/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"

#include <QDialog>

namespace TextAddonsWidgets
{
class SelectSpecialCharDialogPrivate;
/*!
 * \class TextAddonsWidgets::SelectSpecialCharDialog
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/SelectSpecialCharDialog
 *
 * \brief The SelectSpecialCharDialog class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT SelectSpecialCharDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for the SelectSpecialCharDialog
     * \param parent The parent widget
     */
    explicit SelectSpecialCharDialog(QWidget *parent);
    /*!
     * \brief Destructor for the SelectSpecialCharDialog
     */
    ~SelectSpecialCharDialog() override;

    /*!
     * Sets the current character to display
     * \param c The character to set
     */
    void setCurrentChar(QChar c);
    /*!
     * Returns the currently selected character
     */
    [[nodiscard]] QChar currentChar() const;

    /*!
     * Sets the text for the OK button
     * \param text The button text
     */
    void setOkButtonText(const QString &text);

    /*!
     * Shows or hides the select button
     * \param show Whether to show the button
     */
    void showSelectButton(bool show);

    /*!
     * When we double click we call accept
     */
    void autoInsertChar();

Q_SIGNALS:
    /*!
     * \brief Emitted when a character is selected
     * \param c The selected character
     */
    void charSelected(QChar);

private:
    friend class SelectSpecialCharDialogPrivate;
    std::unique_ptr<SelectSpecialCharDialogPrivate> const d;
};
}
