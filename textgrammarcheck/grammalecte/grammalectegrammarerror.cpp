/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectegrammarerror.h"
#include "textgrammarcheck_debug.h"

#include <QJsonArray>

using namespace TextGrammarCheck;

GrammalecteGrammarError::GrammalecteGrammarError() = default;

GrammalecteGrammarError::~GrammalecteGrammarError() = default;

QStringList GrammalecteGrammarError::parseSuggestion(const QJsonObject &obj)
{
    QStringList lst;
    const QJsonArray array = obj[QLatin1StringView("aSuggestions")].toArray();
    const QVariantList list = array.toVariantList();
    lst.reserve(list.count());
    for (const QVariant &v : list) {
        // qDebug() << " v" << v.toString();
        lst.append(v.toString());
    }
    return lst;
}

QColor GrammalecteGrammarError::parseColor(const QJsonObject &obj)
{
    QColor col;
    const QJsonArray array = obj[QLatin1StringView("aColor")].toArray();
    if (array.isEmpty()) {
        return col;
    }
    if (array.count() == 3) {
        // const QVariantList list = array.toVariantList();
        //        for (const QVariant &v : list) {
        //            qDebug() << " v" << v.toInt();
        //        }
        col = QColor(array.at(0).toInt(), array.at(1).toInt(), array.at(2).toInt());
    } else {
        qCWarning(TEXTGRAMMARCHECK_LOG) << "Parsing color: Array is not correct:" << array;
    }
    return col;
}

void GrammalecteGrammarError::parse(const QJsonObject &obj, int blockindex)
{
    const int end = obj[QLatin1StringView("nEnd")].toInt(-1);
    mStart = obj[QLatin1StringView("nStart")].toInt(-1);
    if (end != -1) {
        mLength = end - mStart;
    }
    mError = obj[QLatin1StringView("sMessage")].toString();
    if (mLength != -1) {
        mBlockId = blockindex;
        mColor = parseColor(obj);
        mSuggestions = parseSuggestion(obj);
    }
    mRule = obj[QLatin1StringView("sRuleId")].toString();
    mOption = obj[QLatin1StringView("sType")].toString();
    mUrl = obj[QLatin1StringView("URL")].toString();
}
