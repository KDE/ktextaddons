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
#include <TextAutoGenerateText/TextAutoGenerateManager>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextInstancesManagerListView::TextAutoGenerateTextInstancesManagerListView(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                           QWidget *parent)
    : QListView(parent)
    , mSortFilterProxyModel(new TextAutoGenerateTextInstanceSortFilterProxyModel(this))
    , mTextAutoGenerateManager(manager)
{
    setItemDelegate(new TextAutoGenerateTextInstancesManagerListViewDelegate(this));
    setDragEnabled(false);
    if (mTextAutoGenerateManager) {
        mSortFilterProxyModel->setSourceModel(mTextAutoGenerateManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel());
    }
    setModel(mSortFilterProxyModel);
    connect(this, &QListView::doubleClicked, this, &TextAutoGenerateTextInstancesManagerListView::slotEditInstance);
}

TextAutoGenerateTextInstancesManagerListView::~TextAutoGenerateTextInstancesManagerListView() = default;

void TextAutoGenerateTextInstancesManagerListView::slotSearchChanged(const QString &str)
{
    mSortFilterProxyModel->setSearchText(str);
}

void TextAutoGenerateTextInstancesManagerListView::slotEditInstance(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateTextInstanceModel::Uuid).toByteArray();
    if (uuid.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "invalid instance uuid";
    } else {
        Q_EMIT editInstance(uuid);
    }
}

void TextAutoGenerateTextInstancesManagerListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    auto addInstanceAction = new QAction(i18nc("@action", "Add instance…"), &menu);
    menu.addAction(addInstanceAction);
    connect(addInstanceAction, &QAction::triggered, this, &TextAutoGenerateTextInstancesManagerListView::addInstance);

    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        menu.addSeparator();
        const bool isDefault = index.data(TextAutoGenerateTextInstanceModel::IsDefault).toBool();
        const bool isEnabled = index.data(TextAutoGenerateTextInstanceModel::Enabled).toBool();
        if (!isDefault && isEnabled) {
            auto markAsDefault = new QAction(i18nc("@action", "Mark As Default"), &menu);
            menu.addAction(markAsDefault);
            menu.addSeparator();
            connect(markAsDefault, &QAction::triggered, this, [this, index] {
                const QByteArray uuid = index.data(TextAutoGenerateTextInstanceModel::Uuid).toByteArray();
                if (uuid.isEmpty()) {
                    qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "invalid instance uuid";
                } else {
                    Q_EMIT markAsDefaultChanged(uuid);
                }
            });
        }

        auto editAction = new QAction(QIcon::fromTheme(u"edit-rename"_s), i18nc("@action", "Edit…"), &menu);
        connect(editAction, &QAction::triggered, this, [index, this]() {
            slotEditInstance(index);
        });
        menu.addAction(editAction);
        menu.addSeparator();
        auto removeAction = new QAction(QIcon::fromTheme(u"list-remove"_s), i18nc("@action", "Remove Instance"), &menu);
        connect(removeAction, &QAction::triggered, this, [index, this]() {
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
                    Q_EMIT removeInstance(uuid);
                }
            }
        });
        menu.addAction(removeAction);
    }
    menu.exec(event->globalPos());
}

#include "moc_textautogeneratetextinstancesmanagerlistview.cpp"
