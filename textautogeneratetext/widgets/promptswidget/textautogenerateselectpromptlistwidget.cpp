/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselectpromptlistwidget.h"
#include "textautogenerateselectpromptdelegate.h"
#include "textautogeneratetextwidget_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectPromptListWidget::TextAutoGenerateSelectPromptListWidget(QWidget *parent)
    : QListView(parent)
{
    setItemDelegate(new TextAutoGenerateSelectPromptDelegate(this));
}

TextAutoGenerateSelectPromptListWidget::~TextAutoGenerateSelectPromptListWidget() = default;

void TextAutoGenerateSelectPromptListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    auto addInstanceAction = new QAction(i18nc("@action", "Add prompt…"), &menu);
    menu.addAction(addInstanceAction);
    connect(addInstanceAction, &QAction::triggered, this, &TextAutoGenerateSelectPromptListWidget::addPrompt);

    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        menu.addSeparator();
        auto editAction = new QAction(QIcon::fromTheme(u"edit-rename"_s), i18nc("@action", "Edit…"), &menu);
        connect(editAction, &QAction::triggered, this, [index, this]() {
            // TODO slotEditPrompt(index);
        });
        menu.addAction(editAction);
        menu.addSeparator();
        auto removeAction = new QAction(QIcon::fromTheme(u"list-remove"_s), i18nc("@action", "Remove Prompt"), &menu);
        connect(removeAction, &QAction::triggered, this, [index, this]() {
#if 0 // TODO
            const QByteArray uuid = index.data(TextAutoGenerateTextInstanceModel::Uuid).toByteArray();
            if (uuid.isEmpty()) {
                qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "invalid instance uuid";
            } else {
                const QString name = index.data(TextAutoGenerateTextInstanceModel::Name).toString();
                if (KMessageBox::warningTwoActions(this,
                                                   i18n("Do you want to remove this instance (%1)?", name),
                                                   i18nc("@title", "Remove Instance"),
                                                   KStandardGuiItem::remove(),
                                                   KStandardGuiItem::cancel())
                    == KMessageBox::PrimaryAction) {
                    Q_EMIT removePrompt(uuid);
                }
            }
#endif
        });
        menu.addAction(removeAction);
    }
    menu.exec(event->globalPos());
}
#include "moc_textautogenerateselectpromptlistwidget.cpp"
