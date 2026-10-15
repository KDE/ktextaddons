/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselectagentlistwidget.h"
#include "core/models/textautogeneratetextagentmodel.h"
#include "textautogenerateagentdialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectAgentListWidget::TextAutoGenerateSelectAgentListWidget(QWidget *parent)
    : QListView(parent)
{
    connect(this, &QListView::doubleClicked, this, &TextAutoGenerateSelectAgentListWidget::slotEditAgent);
}

TextAutoGenerateSelectAgentListWidget::~TextAutoGenerateSelectAgentListWidget() = default;

void TextAutoGenerateSelectAgentListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    auto addAction = new QAction(QIcon::fromTheme(u"list-add"_s), i18nc("@action", "Add Agent…"), &menu);
    menu.addAction(addAction);
    connect(addAction, &QAction::triggered, this, &TextAutoGenerateSelectAgentListWidget::slotAddAgent);

    if (const QModelIndex index = indexAt(event->pos()); index.isValid()) {
        menu.addSeparator();
        auto editAction = new QAction(QIcon::fromTheme(u"edit-rename"_s), i18nc("@action", "Edit…"), &menu);
        connect(editAction, &QAction::triggered, this, [index, this]() {
            slotEditAgent(index);
        });
        menu.addAction(editAction);
        if (const QByteArray identifier = index.data(TextAutoGenerateTextAgentModel::Identifier).toByteArray(); !identifier.isEmpty()) {
            menu.addSeparator();
            const QString name = index.data(TextAutoGenerateTextAgentModel::Name).toString();
            auto removeAction = new QAction(QIcon::fromTheme(u"list-remove"_s), i18nc("@action", "Remove Agent"), &menu);
            connect(removeAction, &QAction::triggered, this, [name, identifier, this]() {
                if (KMessageBox::warningTwoActions(this,
                                                   i18n("Do you want to remove this agent (%1)?", name),
                                                   i18nc("@title", "Remove Agent"),
                                                   KStandardGuiItem::remove(),
                                                   KStandardGuiItem::cancel())
                    == KMessageBox::PrimaryAction) {
                    Q_EMIT removeAgent(identifier);
                }
            });
            menu.addAction(removeAction);
        }
    }
    menu.exec(event->globalPos());
}

void TextAutoGenerateSelectAgentListWidget::slotAddAgent()
{
    TextAutoGenerateAgentDialog dlg(this);
    if (dlg.exec()) {
        Q_EMIT addAgent(dlg.agent());
    }
}

void TextAutoGenerateSelectAgentListWidget::slotEditAgent(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    TextAutoGenerateAgentDialog dlg(this);
    dlg.setAgent(index.data(TextAutoGenerateTextAgentModel::Agent).value<TextAutoGenerateText::TextAutoGenerateAgent>());
    if (dlg.exec()) {
        Q_EMIT editAgent(dlg.agent());
    }
}

#include "moc_textautogenerateselectagentlistwidget.cpp"
