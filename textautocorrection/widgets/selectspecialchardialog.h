/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautocorrectionwidgets_export.h"

#include <QDialog>

namespace TextAutoCorrectionWidgets
{
class SelectSpecialCharDialogPrivate;
/**
 * @brief The SelectSpecialCharDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONWIDGETS_EXPORT SelectSpecialCharDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectSpecialCharDialog(QWidget *parent);
    ~SelectSpecialCharDialog() override;

    void setCurrentChar(QChar c);
    Q_REQUIRED_RESULT QChar currentChar() const;

    void setOkButtonText(const QString &text);

    void showSelectButton(bool show);

    /*
     * When we double click we call accept
     */
    void autoInsertChar();

Q_SIGNALS:
    void charSelected(QChar);

private:
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void readConfig();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void writeConfig();
    friend class SelectSpecialCharDialogPrivate;
    std::unique_ptr<SelectSpecialCharDialogPrivate> const d;
};
}
