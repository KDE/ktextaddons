/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
#include <TextAutoGenerateText/TextAutoGenerateTag>
namespace TextAutoGenerateText
{
class TextAutoGenerateManageTagsWidget;
/**
 * @brief The TextAutoGenerateManageTagsDialog class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateManageTagsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManageTagsDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateManageTagsDialog() override;

    /*! Fills the dialog with \a tags. */
    void setTags(const QList<TextAutoGenerateText::TextAutoGenerateTag> &tags);
    /*! Returns the edited tags. */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTag> tags() const;

private:
    TextAutoGenerateManageTagsWidget *const mManageTagsWidget;
};
}
