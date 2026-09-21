/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
#include <TextAutoGenerateText/TextAutoGenerateTag>
class QPushButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateTagWidget;
/**
 * @brief The TextAutoGenerateTagDialog class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTagDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTagDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateTagDialog() override;

    /*! Fills the dialog with \a tag and switches the window title to edition mode. */
    void setTag(const TextAutoGenerateText::TextAutoGenerateTag &tag);
    /*! Returns the edited tag. */
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTag tag() const;

private:
    TextAutoGenerateTagWidget *const mTagWidget;
    QPushButton *mOkButton = nullptr;
};
}
