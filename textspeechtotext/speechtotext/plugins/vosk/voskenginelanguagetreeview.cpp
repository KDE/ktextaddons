/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskenginelanguagetreeview.h"

VoskEngineLanguageTreeView::VoskEngineLanguageTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setRootIsDecorated(false);
    setSortingEnabled(true);
}

VoskEngineLanguageTreeView::~VoskEngineLanguageTreeView() = default;
