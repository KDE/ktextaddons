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
}

VoskEngineLanguageTreeView::~VoskEngineLanguageTreeView() = default;

void VoskEngineLanguageTreeView::slotCustomContextMenuRequested(const QPoint &pos)
{
    const QModelIndex index = indexAt(pos);
    if (index.isValid()) {
        QMenu menu(this);
        menu.addAction(i18nc("@action", "Mark as Active"), this, [this, index]() {
            // TODO removeClicked(index.siblingAtColumn(VoskSpeechToTextModel::Identifier).data().toByteArray());
        });
        menu.exec(viewport()->mapToGlobal(pos));
    }
}

#include "moc_voskenginelanguagetreeview.cpp"
