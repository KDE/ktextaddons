/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "needupdateparsehtmlutil.h"
#include <QRegularExpression>

using namespace Qt::Literals::StringLiterals;

QString TextAddonsWidgets::NeedUpdateParseHtmlUtil::extractDate(const QString &dataHtml)
{
    if (dataHtml.isEmpty()) {
        return {};
    }
    // By default generated html page will not changed in the future
    static const QRegularExpression reg(u"<td align=\"right\">(\\d+\\-\\d\\d\\-\\d\\d).*<"_s);

    if (const QRegularExpressionMatch match = reg.match(dataHtml); match.hasMatch()) {
        const QString matched = match.captured(1);
        return matched;
    }
    return {};
}
