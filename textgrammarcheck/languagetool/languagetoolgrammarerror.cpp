/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgrammarerror.h"
#include "languagetoolmanager.h"
#include "textgrammarcheck_debug.h"

#include <QJsonArray>
using namespace TextGrammarCheck;
LanguageToolGrammarError::LanguageToolGrammarError() = default;

LanguageToolGrammarError::~LanguageToolGrammarError() = default;

void LanguageToolGrammarError::parse(const QJsonObject &obj, int blockindex)
{
    // We use block id index based on 1 in API
    mBlockId = blockindex;
    mError = obj[QLatin1String("message")].toString();
    mStart = obj[QLatin1String("offset")].toInt(-1);
    mLength = obj[QLatin1String("length")].toInt(-1);
    mSuggestions = parseSuggestion(obj);
    const QJsonObject rulesObj = obj[QLatin1String("rule")].toObject();
    if (!rulesObj.isEmpty()) {
        mRule = rulesObj[QLatin1String("id")].toString();
        const QJsonArray urlArray = rulesObj[QLatin1String("urls")].toArray();
        if (!urlArray.isEmpty()) {
            if (urlArray.count() > 1) {
                qCWarning(TEXTGRAMMARCHECK_LOG) << "LanguageToolGrammarError::parse : more than 1 url found. Perhaps need to adapt api ";
            }
            mUrl = urlArray.at(0)[QLatin1String("value")].toString();
            // qDebug() << " mUrl" << mUrl;
        }
    }
    if (!mRule.isEmpty() && !mTesting) {
        mColor = LanguageToolManager::self()->grammarColorForError(mRule);
    } else {
        mColor = QColor(Qt::red);
    }
}

void LanguageToolGrammarError::setTesting(bool b)
{
    mTesting = b;
}

QStringList LanguageToolGrammarError::parseSuggestion(const QJsonObject &obj)
{
    QStringList lst;
    const QJsonArray array = obj[QLatin1String("replacements")].toArray();
    for (const QJsonValue &current : array) {
        if (current.type() == QJsonValue::Object) {
            const QJsonObject suggestionObject = current.toObject();
            lst.append(suggestionObject[QLatin1String("value")].toString());
        }
    }
    // qDebug() << " lst : " << lst;
    return lst;
}
