/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteparser.h"

#include "grammalectegrammarerror.h"
#include "textgrammarcheck_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

using namespace TextGrammarCheck;
using namespace Qt::Literals::StringLiterals;

GrammalecteParser::GrammalecteParser() = default;

GrammalecteParser::~GrammalecteParser() = default;

QVector<GrammarError> GrammalecteParser::parseResult(const QJsonObject &obj) const
{
    QVector<GrammarError> infos;
    if (!obj.contains("grammalecte"_L1)) {
        qCWarning(TEXTGRAMMARCHECK_LOG) << "Error in json " << obj;
        return infos;
    }
    const QJsonArray array = obj.value("data"_L1).toArray();
    for (const QJsonValue &current : array) {
        if (current.type() == QJsonValue::Object) {
            // Check lGrammarErrors
            const QJsonObject grammaObject = current.toObject();
            const int blockId = grammaObject.value(u"iParagraph"_s).toInt();
            // qDebug() << " blockId " << blockId;
            const QJsonArray grammarErrorArray = grammaObject.value("lGrammarErrors"_L1).toArray();
            for (const QJsonValue &error : grammarErrorArray) {
                // qDebug() << " grammarErrorArray"<<error;
                TextGrammarCheck::GrammalecteGrammarError info;
                if (error.type() == QJsonValue::Object) {
                    info.parse(error.toObject(), blockId);
                    if (info.isValid()) {
                        infos.append(std::move(info));
                    }
                } else {
                    qCWarning(TEXTGRAMMARCHECK_LOG) << "Problem when parsing grammalecte error" << error;
                }
            }
        } else {
            qCWarning(TEXTGRAMMARCHECK_LOG) << "Problem when parsing grammalecte result" << current;
        }
    }
    return infos;
}
