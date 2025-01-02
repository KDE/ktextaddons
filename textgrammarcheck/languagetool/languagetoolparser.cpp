/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolparser.h"
using namespace Qt::Literals::StringLiterals;

#include "languagetoolgrammarerror.h"

#include <QJsonArray>

using namespace TextGrammarCheck;

LanguageToolParser::LanguageToolParser() = default;

LanguageToolParser::~LanguageToolParser() = default;

QVector<GrammarError> LanguageToolParser::parseResult(const QJsonObject &obj) const
{
    QVector<GrammarError> infos;
    const QJsonArray array = obj.value("matches"_L1).toArray();
    for (const QJsonValue &current : array) {
        // qDebug() << " current " << current;
        if (current.type() == QJsonValue::Object) {
            const QJsonObject languageToolObject = current.toObject();
            LanguageToolGrammarError error;
            error.parse(languageToolObject, -1);
            if (error.isValid()) {
                infos.append(error);
            }
        }
    }
    return infos;
}
