/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "whatsnewngutils.h"
#include <QCryptographicHash>

QString TextAddonsWidgets::WhatsNewNgUtils::createMD5(const QString &str)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(str.toLatin1());
    return QLatin1StringView(md5.result().toBase64());
}
