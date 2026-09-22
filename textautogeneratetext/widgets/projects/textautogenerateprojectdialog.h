/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
#include <TextAutoGenerateText/TextAutoGenerateProject>
class QPushButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateProjectWidget;
/**
 * @brief The TextAutoGenerateProjectDialog class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateProjectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateProjectDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateProjectDialog() override;

    /*! Fills the dialog with \a project and switches the window title to edition mode. */
    void setProject(const TextAutoGenerateText::TextAutoGenerateProject &project);
    /*! Returns the edited project. */
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateProject project() const;

private:
    TextAutoGenerateProjectWidget *const mProjectWidget;
    QPushButton *mOkButton = nullptr;
};
}
