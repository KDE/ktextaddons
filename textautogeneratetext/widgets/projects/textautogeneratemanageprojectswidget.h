/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateProject>
class QListView;
class QModelIndex;
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateProjectsModel;
/**
 * @brief The TextAutoGenerateManageProjectsWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateManageProjectsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManageProjectsWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateManageProjectsWidget() override;

    /*! Fills the widget with \a projects. The widget works on a copy: projects() returns the edited list. */
    void setProjects(const QList<TextAutoGenerateText::TextAutoGenerateProject> &projects);
    /*! Returns the edited projects. */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateProject> projects() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddProject();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotModifyProject();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveProject();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotModifyProject(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateButtons();
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateText::TextAutoGenerateProject projectFromIndex(const QModelIndex &index) const;
    QListView *const mProjectsListView;
    TextAutoGenerateProjectsModel *const mProjectsModel;
    QToolButton *const mAddButton;
    QToolButton *const mModifyButton;
    QToolButton *const mRemoveButton;
};
}
