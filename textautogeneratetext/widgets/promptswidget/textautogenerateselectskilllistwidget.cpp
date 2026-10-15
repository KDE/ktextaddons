/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselectskilllistwidget.h"
#include "core/models/textautogeneratetextskillmodel.h"
#include "textautogenerateskilldialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectSkillListWidget::TextAutoGenerateSelectSkillListWidget(QWidget *parent)
    : QListView(parent)
{
    connect(this, &QListView::doubleClicked, this, &TextAutoGenerateSelectSkillListWidget::slotEditSkill);
}

TextAutoGenerateSelectSkillListWidget::~TextAutoGenerateSelectSkillListWidget() = default;

void TextAutoGenerateSelectSkillListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    auto addAction = new QAction(QIcon::fromTheme(u"list-add"_s), i18nc("@action", "Add Skill…"), &menu);
    menu.addAction(addAction);
    connect(addAction, &QAction::triggered, this, &TextAutoGenerateSelectSkillListWidget::slotAddSkill);

    if (const QModelIndex index = indexAt(event->pos()); index.isValid()) {
        menu.addSeparator();
        auto editAction = new QAction(QIcon::fromTheme(u"edit-rename"_s), i18nc("@action", "Edit…"), &menu);
        connect(editAction, &QAction::triggered, this, [index, this]() {
            slotEditSkill(index);
        });
        menu.addAction(editAction);
        if (const QByteArray identifier = index.data(TextAutoGenerateTextSkillModel::Identifier).toByteArray(); !identifier.isEmpty()) {
            menu.addSeparator();
            const QString name = index.data(TextAutoGenerateTextSkillModel::Name).toString();
            auto removeAction = new QAction(QIcon::fromTheme(u"list-remove"_s), i18nc("@action", "Remove Skill"), &menu);
            connect(removeAction, &QAction::triggered, this, [name, identifier, this]() {
                if (KMessageBox::warningTwoActions(this,
                                                   i18n("Do you want to remove this skill (%1)?", name),
                                                   i18nc("@title", "Remove Skill"),
                                                   KStandardGuiItem::remove(),
                                                   KStandardGuiItem::cancel())
                    == KMessageBox::PrimaryAction) {
                    Q_EMIT removeSkill(identifier);
                }
            });
            menu.addAction(removeAction);
        }
    }
    menu.exec(event->globalPos());
}

void TextAutoGenerateSelectSkillListWidget::slotAddSkill()
{
    TextAutoGenerateSkillDialog dlg(this);
    if (dlg.exec()) {
        Q_EMIT addSkill(dlg.skill());
    }
}

void TextAutoGenerateSelectSkillListWidget::slotEditSkill(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    TextAutoGenerateSkillDialog dlg(this);
    dlg.setSkill(index.data(TextAutoGenerateTextSkillModel::Skill).value<TextAutoGenerateText::TextAutoGenerateSkill>());
    if (dlg.exec()) {
        Q_EMIT editSkill(dlg.skill());
    }
}

#include "moc_textautogenerateselectskilllistwidget.cpp"
