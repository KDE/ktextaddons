/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QMenu>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
/**
 * @brief The TextAutoGenerateProjectsMenu class
 *
 * A menu which moves a chat to a project: one exclusive checkable action per project, plus an entry
 * which removes the chat from its project and one which opens the projects management dialog.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateProjectsMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TextAutoGenerateProjectsMenu(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateProjectsMenu() override;

    /*! Rebuilds the menu for the chat identified by \a chatId. An empty identifier only leaves the
     *  management entry, as there is then no chat to move. */
    void setChatId(const QByteArray &chatId);
    /*! Returns the chat the menu moves to a project. */
    [[nodiscard]] QByteArray chatId() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateMenu();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAssignProject(const QByteArray &identifier);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotManageProjects();
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QByteArray mChatId;
};
}
