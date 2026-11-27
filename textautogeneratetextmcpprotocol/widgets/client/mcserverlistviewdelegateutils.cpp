/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcserverlistviewdelegateutils.h"

#include <QFont>

QFont McServerListViewDelegateUtils::nameFont(const QFont &font)
{
    QFont f = font;
    f.setBold(true);
    return f;
}

QFont McServerListViewDelegateUtils::descriptionFont(const QFont &font)
{
    QFont f = font;
    if (f.pointSizeF() > 0) {
        f.setPointSizeF(qMax(1.0, f.pointSizeF() - 1));
    } else if (f.pixelSize() > 0) {
        f.setPixelSize(qMax(1, f.pixelSize() - 1));
    }
    return f;
}
