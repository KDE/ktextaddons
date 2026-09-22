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
 * @brief The TextAutoGenerateTagsMenu class
 *
 * A menu which assigns the known tags to a chat: one checkable action per tag, plus an entry which
 * opens the tags management dialog.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTagsMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTagsMenu(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateTagsMenu() override;

    /*! Rebuilds the menu for the chat identified by \a chatId. An empty identifier only leaves the
     *  management entry, as there is then no chat to assign a tag to. */
    void setChatId(const QByteArray &chatId);
    /*! Returns the chat the menu assigns tags to. */
    [[nodiscard]] QByteArray chatId() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateMenu();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAssignTag(const QByteArray &identifier, bool assign);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotManageTags();
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QByteArray mChatId;
};
}
