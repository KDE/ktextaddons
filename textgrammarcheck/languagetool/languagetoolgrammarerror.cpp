/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgrammarerror.h"

#include "languagetoolmanager.h"
#include "textgrammarcheck_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextGrammarCheck;
LanguageToolGrammarError::LanguageToolGrammarError() = default;

LanguageToolGrammarError::~LanguageToolGrammarError() = default;

void LanguageToolGrammarError::parse(const QJsonObject &obj, int blockindex)
{
    // We use block id index based on 1 in API
    mBlockId = blockindex;
    mError = obj["message"_L1].toString();
    mStart = obj["offset"_L1].toInt(-1);
    mLength = obj["length"_L1].toInt(-1);
    mSuggestions = parseSuggestion(obj);
    const QJsonObject rulesObj = obj["rule"_L1].toObject();
    if (!rulesObj.isEmpty()) {
        mRule = rulesObj["id"_L1].toString();
        const QJsonArray urlArray = rulesObj["urls"_L1].toArray();
        if (!urlArray.isEmpty()) {
            if (urlArray.count() > 1) {
                qCWarning(TEXTGRAMMARCHECK_LOG) << "LanguageToolGrammarError::parse : more than 1 url found. Perhaps need to adapt api ";
            }
            mUrl = urlArray.at(0)["value"_L1].toString();
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
    const QJsonArray array = obj["replacements"_L1].toArray();
    for (const QJsonValue &current : array) {
        if (current.type() == QJsonValue::Object) {
            const QJsonObject suggestionObject = current.toObject();
            lst.append(suggestionObject["value"_L1].toString());
        }
    }
    // qDebug() << " lst : " << lst;
    return lst;
}
