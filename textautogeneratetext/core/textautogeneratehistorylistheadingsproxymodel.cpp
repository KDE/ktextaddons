/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistheadingsproxymodel.h"

using namespace TextAutogenerateText;
TextAutoGenerateHistoryListHeadingsProxyModel::TextAutoGenerateHistoryListHeadingsProxyModel(QObject *parent)
    : QAbstractProxyModel{parent}
{
}

TextAutoGenerateHistoryListHeadingsProxyModel::~TextAutoGenerateHistoryListHeadingsProxyModel() = default;
