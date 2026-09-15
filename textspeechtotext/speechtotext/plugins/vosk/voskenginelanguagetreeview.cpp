/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskenginelanguagetreeview.h"
#include "voskspeechtotextmodel.h"
#include <KLocalizedString>
#include <QMenu>

VoskEngineLanguageTreeView::VoskEngineLanguageTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setRootIsDecorated(false);
    setSortingEnabled(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &VoskEngineLanguageTreeView::customContextMenuRequested, this, &VoskEngineLanguageTreeView::slotCustomContextMenuRequested);
}

VoskEngineLanguageTreeView::~VoskEngineLanguageTreeView() = default;

void VoskEngineLanguageTreeView::slotCustomContextMenuRequested(const QPoint &pos)
{
    const QModelIndex index = indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    QMenu menu(this);
    // TODO add install action too
    const bool installed = !index.siblingAtColumn(VoskSpeechToTextModel::Installed).data().toString().isEmpty();
    const bool active = !index.siblingAtColumn(VoskSpeechToTextModel::Active).data().toString().isEmpty();
    if (installed && !active) {
        const QString name = index.siblingAtColumn(VoskSpeechToTextModel::Name).data().toString();
        menu.addAction(i18nc("@action", "Mark as Active"), this, [this, name]() {
            Q_EMIT markAsActive(name);
        });
    }
    if (!menu.isEmpty()) {
        menu.exec(viewport()->mapToGlobal(pos));
    }
}

#include "moc_voskenginelanguagetreeview.cpp"
