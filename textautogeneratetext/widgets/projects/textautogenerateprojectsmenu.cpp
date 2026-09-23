/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprojectsmenu.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogenerateprojectsmanager.h"
#include "textautogeneratemanageprojectsdialog.h"
#include <KLocalizedString>
#include <QActionGroup>
#include <QPixmap>
#include <QPointer>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateProjectsMenu::TextAutoGenerateProjectsMenu(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QMenu(parent)
    , mManager(manager)
{
    setObjectName(u"TextAutoGenerateProjectsMenu"_s);
    setTitle(i18nc("@title:menu", "Project"));
    setIcon(QIcon::fromTheme(u"folder"_s));
    updateMenu();
}

TextAutoGenerateProjectsMenu::~TextAutoGenerateProjectsMenu() = default;

void TextAutoGenerateProjectsMenu::setChatId(const QByteArray &chatId)
{
    mChatId = chatId;
    updateMenu();
}

QByteArray TextAutoGenerateProjectsMenu::chatId() const
{
    return mChatId;
}

void TextAutoGenerateProjectsMenu::updateMenu()
{
    clear();
    if (mManager && !mChatId.isEmpty()) {
        const QList<TextAutoGenerateProject> projects = mManager->textAutoGenerateProjectsManager()->projects();
        if (!projects.isEmpty()) {
            // A chat belongs to at most one project, so the actions are exclusive.
            auto projectsGroup = new QActionGroup(this);
            const QByteArray assignedProject = mManager->chatProject(mChatId);

            auto noProjectAction = new QAction(i18nc("@action", "No Project"), this);
            noProjectAction->setObjectName(u"noProjectAction"_s);
            noProjectAction->setCheckable(true);
            noProjectAction->setChecked(assignedProject.isEmpty());
            projectsGroup->addAction(noProjectAction);
            connect(noProjectAction, &QAction::triggered, this, [this]() {
                slotAssignProject({});
            });
            addAction(noProjectAction);

            addSeparator();

            for (const TextAutoGenerateProject &project : projects) {
                auto projectAction = new QAction(QIcon::fromTheme(project.iconName()), project.name(), this);
                projectAction->setCheckable(true);
                projectAction->setChecked(project.identifier() == assignedProject);
                projectsGroup->addAction(projectAction);
                const QByteArray identifier = project.identifier();
                connect(projectAction, &QAction::triggered, this, [this, identifier]() {
                    slotAssignProject(identifier);
                });
                addAction(projectAction);
            }
            addSeparator();
        }
    }
    auto manageProjectsAction = new QAction(QIcon::fromTheme(u"folder"_s), i18nc("@action", "Manage Projects…"), this);
    manageProjectsAction->setObjectName(u"manageProjectsAction"_s);
    connect(manageProjectsAction, &QAction::triggered, this, &TextAutoGenerateProjectsMenu::slotManageProjects);
    addAction(manageProjectsAction);
}

void TextAutoGenerateProjectsMenu::slotAssignProject(const QByteArray &identifier)
{
    if (!mManager || mChatId.isEmpty()) {
        return;
    }
    mManager->setChatProject(mChatId, identifier);
}

void TextAutoGenerateProjectsMenu::slotManageProjects()
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
    QPointer<TextAutoGenerateManageProjectsDialog> dialog(new TextAutoGenerateManageProjectsDialog(dialogParent));
    dialog->setProjects(mManager->textAutoGenerateProjectsManager()->projects());
    if (dialog->exec()) {
        mManager->updateProjects(dialog->projects());
        updateMenu();
    }
    delete dialog;
}

#include "moc_textautogenerateprojectsmenu.cpp"
