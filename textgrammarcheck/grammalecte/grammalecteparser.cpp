/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteparser.h"
#include "grammalectegrammarerror.h"
#include "textgrammarcheck_debug.h"
#include <QJsonArray>
#include <QJsonValue>

using namespace TextGrammarCheck;

GrammalecteParser::GrammalecteParser() = default;

GrammalecteParser::~GrammalecteParser() = default;

QVector<GrammarError> GrammalecteParser::parseResult(const QJsonObject &obj) const
{
    QVector<GrammarError> infos;
    if (!obj.contains(QLatin1StringView("grammalecte"))) {
        qCWarning(TEXTGRAMMARCHECK_LOG) << "Error in json " << obj;
        return infos;
    }
    const QJsonArray array = obj.value(QLatin1StringView("data")).toArray();
    for (const QJsonValue &current : array) {
        if (current.type() == QJsonValue::Object) {
            // Check lGrammarErrors
            const QJsonObject grammaObject = current.toObject();
            const int blockId = grammaObject.value(QStringLiteral("iParagraph")).toInt();
            // qDebug() << " blockId " << blockId;
            const QJsonArray grammarErrorArray = grammaObject.value(QLatin1StringView("lGrammarErrors")).toArray();
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
