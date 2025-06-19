/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagerlistview.h"
#include "core/models/textautogeneratetextinstancemodel.h"
#include "core/models/textautogeneratetextinstancesortfilterproxymodel.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "textautogeneratetextinstancesmanagerlistviewdelegate.h"
#include "textautogeneratetextwidget_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
#include <QSortFilterProxyModel>
#include <TextAutoGenerateText/TextAutoGenerateManager>
using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerListView::TextAutoGenerateTextInstancesManagerListView(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                           QWidget *parent)
    : QListView(parent)
    , mSortFilterProxyModel(new TextAutoGenerateTextInstanceSortFilterProxyModel(this))
    , mTextAutoGenerateManager(manager)
{
    setItemDelegate(new TextAutoGenerateTextInstancesManagerListViewDelegate(this));
    mSortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    setDragEnabled(false);
    if (mTextAutoGenerateManager) {
        mSortFilterProxyModel->setSourceModel(mTextAutoGenerateManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel());
    }
    setModel(mSortFilterProxyModel);
}

TextAutoGenerateTextInstancesManagerListView::~TextAutoGenerateTextInstancesManagerListView() = default;

void TextAutoGenerateTextInstancesManagerListView::slotSearchChanged(const QString &str)
{
    mSortFilterProxyModel->setSearchText(str);
}

void TextAutoGenerateTextInstancesManagerListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        auto editAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-rename")), i18nc("@action", "Edit…"), &menu);
        connect(editAction, &QAction::triggered, this, [index, this]() {
            const QByteArray uuid = index.data(TextAutoGenerateTextInstanceModel::Uuid).toByteArray();
            if (uuid.isEmpty()) {
                qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "invalid instance uuid";
            } else {
                Q_EMIT editInstance(index.data(TextAutoGenerateTextInstanceModel::Uuid).toByteArray());
            }
        });
        menu.addAction(editAction);
        menu.addSeparator();
        auto removeAction = new QAction(QIcon::fromTheme(QStringLiteral("list-remove")), i18nc("@action", "Remove Instance"), &menu);
        connect(removeAction, &QAction::triggered, this, [index, this]() {
            const QByteArray uuid = index.data(TextAutoGenerateTextInstanceModel::Uuid).toByteArray();
            if (uuid.isEmpty()) {
                qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "invalid instance uuid";
            } else {
                // TODO add instance name ?
                if (KMessageBox::warningTwoActions(this,
                                                   i18n("Do you want to remove this instance?"),
                                                   i18nc("@title", "Remove"),
                                                   KStandardGuiItem::remove(),
                                                   KStandardGuiItem::cancel())
                    == KMessageBox::PrimaryAction) {
                    Q_EMIT removeInstance(index.data(TextAutoGenerateTextInstanceModel::Uuid).toByteArray());
                }
            }
        });
        menu.addAction(removeAction);
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

#include "moc_textautogeneratetextinstancesmanagerlistview.cpp"
