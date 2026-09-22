/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetagsmenu.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetagsmanager.h"
#include "textautogeneratemanagetagsdialog.h"
#include <KLocalizedString>
#include <QPixmap>
#include <QPointer>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

namespace
{
QIcon iconFromColor(const QColor &color)
{
    if (!color.isValid()) {
        return {};
    }
    QPixmap pix(16, 16);
    pix.fill(color);
    return QIcon(pix);
}
}

TextAutoGenerateTagsMenu::TextAutoGenerateTagsMenu(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QMenu(parent)
    , mManager(manager)
{
    setObjectName(u"TextAutoGenerateTagsMenu"_s);
    setTitle(i18nc("@title:menu", "Tags"));
    setIcon(QIcon::fromTheme(u"tag"_s));
    updateMenu();
}

TextAutoGenerateTagsMenu::~TextAutoGenerateTagsMenu() = default;

void TextAutoGenerateTagsMenu::setChatId(const QByteArray &chatId)
{
    mChatId = chatId;
    updateMenu();
}

QByteArray TextAutoGenerateTagsMenu::chatId() const
{
    return mChatId;
}

void TextAutoGenerateTagsMenu::updateMenu()
{
    clear();
    if (mManager && !mChatId.isEmpty()) {
        const QList<QByteArray> assignedTags = mManager->chatTags(mChatId);
        const QList<TextAutoGenerateTag> tags = mManager->textAutoGenerateTagsManager()->tags();
        for (const TextAutoGenerateTag &tag : tags) {
            auto tagAction = new QAction(iconFromColor(tag.color()), tag.name(), this);
            tagAction->setCheckable(true);
            tagAction->setChecked(assignedTags.contains(tag.identifier()));
            const QByteArray identifier = tag.identifier();
            connect(tagAction, &QAction::triggered, this, [this, identifier](bool checked) {
                slotAssignTag(identifier, checked);
            });
            addAction(tagAction);
        }
        if (!tags.isEmpty()) {
            addSeparator();
        }
    }
    auto manageTagsAction = new QAction(QIcon::fromTheme(u"tag"_s), i18nc("@action", "Manage Tags…"), this);
    manageTagsAction->setObjectName(u"manageTagsAction"_s);
    connect(manageTagsAction, &QAction::triggered, this, &TextAutoGenerateTagsMenu::slotManageTags);
    addAction(manageTagsAction);
}

void TextAutoGenerateTagsMenu::slotAssignTag(const QByteArray &identifier, bool assign)
{
    if (!mManager || mChatId.isEmpty()) {
        return;
    }
    QList<QByteArray> tags = mManager->chatTags(mChatId);
    if (assign) {
        if (tags.contains(identifier)) {
            return;
        }
        tags.append(identifier);
    } else if (tags.removeAll(identifier) == 0) {
        return;
    }
    mManager->setChatTags(mChatId, tags);
}

void TextAutoGenerateTagsMenu::slotManageTags()
{
    if (!mManager) {
        return;
    }
    // The menu is parented to the menu which shows it: a popup is a poor dialog parent, use the
    // widget which owns the menus instead.
    QWidget *dialogParent = parentWidget();
    while (auto parentMenu = qobject_cast<QMenu *>(dialogParent)) {
        dialogParent = parentMenu->parentWidget();
    }
    QPointer<TextAutoGenerateManageTagsDialog> dialog(new TextAutoGenerateManageTagsDialog(dialogParent));
    dialog->setTags(mManager->textAutoGenerateTagsManager()->tags());
    if (dialog->exec()) {
        mManager->updateTags(dialog->tags());
        updateMenu();
    }
    delete dialog;
}

#include "moc_textautogeneratetagsmenu.cpp"
