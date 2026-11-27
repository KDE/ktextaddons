/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QFont>

namespace McServerListViewDelegateUtils
{
[[nodiscard]] QFont nameFont(const QFont &font);
[[nodiscard]] QFont descriptionFont(const QFont &font);
};
