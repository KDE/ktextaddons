/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
#include <TextAutoGenerateText/TextAutoGenerateProject>
namespace TextAutoGenerateText
{
class TextAutoGenerateManageProjectsWidget;
/**
 * @brief The TextAutoGenerateManageProjectsDialog class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateManageProjectsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManageProjectsDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateManageProjectsDialog() override;

    /*! Fills the dialog with \a projects. */
    void setProjects(const QList<TextAutoGenerateText::TextAutoGenerateProject> &projects);
    /*! Returns the edited projects. */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateProject> projects() const;

private:
    TextAutoGenerateManageProjectsWidget *const mManageProjectsWidget;
};
}
