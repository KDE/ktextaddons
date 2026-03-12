/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpserverlistview.h"
#include "textautogeneratetextwidget_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextMcpServerListView::TextAutoGenerateTextMcpServerListView(QWidget *parent)
    : QListView(parent)
{
    setDragEnabled(false);
#if 0
    if (mTextAutoGenerateManager) {
        mSortFilterProxyModel->setSourceModel(mTextAutoGenerateManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel());
    }
    setModel(mSortFilterProxyModel);
    connect(this, &QListView::doubleClicked, this, &TextAutoGenerateTextInstancesManagerListView::slotEditInstance);
#endif
}

TextAutoGenerateTextMcpServerListView::~TextAutoGenerateTextMcpServerListView() = default;

void TextAutoGenerateTextMcpServerListView::slotSearchChanged(const QString &str)
{
    // mSortFilterProxyModel->setSearchText(str);
}

void TextAutoGenerateTextMcpServerListView::slotEditMcpServer(const QModelIndex &index)
{
#if 0
    const QByteArray uuid = index.data(TextAutoGenerateTextInstanceModel::Uuid).toByteArray();
    if (uuid.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "invalid instance uuid";
    } else {
        Q_EMIT editInstance(uuid);
    }
#endif
}

void TextAutoGenerateTextMcpServerListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    auto addInstanceAction = new QAction(i18nc("@action", "Add instance…"), &menu);
    menu.addAction(addInstanceAction);
#if 0
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
#endif
    menu.exec(event->globalPos());
}

#include "moc_textautogeneratetextmcpserverlistview.cpp"
