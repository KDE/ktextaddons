/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemenulistview.h"

#include "textautogeneratemenulistviewdelegate.h"
#include "textautogeneratemenumodel.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateMenuListView::TextAutoGenerateMenuListView(QWidget *parent)
    : QListView(parent)
    , mModel(new TextAutoGenerateMenuModel(this))
{
    setDragEnabled(false);
    setModel(mModel);
    setItemDelegate(new TextAutoGenerateMenuListViewDelegate(this));
}

TextAutoGenerateMenuListView::~TextAutoGenerateMenuListView() = default;

void TextAutoGenerateMenuListView::setTextInfos(const QList<TextAutoGenerateMenuTextInfo> &infos)
{
    mModel->setTextInfos(infos);
}

QList<TextAutoGenerateMenuTextInfo> TextAutoGenerateMenuListView::textInfos() const
{
    return mModel->textInfos();
}

void TextAutoGenerateMenuListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    auto addAction = new QAction(QIcon::fromTheme(u"list-add"_s), i18nc("@action", "Add…"), &menu);
    connect(addAction, &QAction::triggered, this, [this]() {
        TextAutoGenerateMenuTextInfo info;
        info.setRequestText(i18n("Ask to AI"));
        mModel->addItem(std::move(info));
    });
    menu.addAction(addAction);
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        auto editAction = new QAction(QIcon::fromTheme(u"document-edit"_s), i18nc("@action", "Modify…"), &menu);
        connect(editAction, &QAction::triggered, this, [index, this]() {
            edit(index);
        });
        menu.addAction(editAction);

        menu.addSeparator();
        auto removeAction = new QAction(QIcon::fromTheme(u"list-remove"_s), i18nc("@action", "Remove…"), &menu);
        connect(removeAction, &QAction::triggered, this, [index, this]() {
            if (KMessageBox::warningTwoActions(this,
                                               i18n("Do you want to remove it?"),
                                               i18nc("@title", "Remove"),
                                               KStandardGuiItem::remove(),
                                               KStandardGuiItem::cancel())
                == KMessageBox::PrimaryAction) {
                mModel->removeInfo(index.row());
            }
        });
        menu.addAction(removeAction);
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

#include "moc_textautogeneratemenulistview.cpp"
