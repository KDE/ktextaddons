/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextreplyinfo.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &t)
{
    d.space() << "totalDuration:" << t.totalDuration;
    d.space() << "loadDuration:" << t.loadDuration;
    d.space() << "promptEvalTokenCount:" << t.promptEvalTokenCount;
    d.space() << "promptEvalDuration:" << t.promptEvalDuration;
    d.space() << "duration:" << t.duration;
    d.space() << "tokenCount:" << t.tokenCount;
    d.space() << "completionTokens:" << t.completionTokens;
    d.space() << "promptTokens:" << t.promptTokens;
    d.space() << "ReplyType:" << TextAutoGenerateTextReplyInfo::convertReplyTypeToString(t.replyType);
    return d;
}

bool TextAutoGenerateTextReplyInfo::isValid() const
{
    return (replyType != ReplyType::Unknown) && (promptEvalTokenCount != 0 || tokenCount != 0 || completionTokens != 0 || promptTokens != 0);
}

QString TextAutoGenerateTextReplyInfo::generateReplyInfo() const
{
    QString info;
    switch (replyType) {
    case ReplyType::Unknown:
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "generateReplyInfo: Invalid type. It's a bug";
        break;
    case ReplyType::Ollama:
        info = generateReplyTypeInfoOllama();
        break;
    case ReplyType::OpenAI:
        info = generateReplyTypeInfoOpenAI();
        break;
    }
    return info;
}

QString TextAutoGenerateTextReplyInfo::generateReplyTypeInfoOllama() const
{
    QString toolTip = i18n("<br><b>Total Duration:</b> %1 seconds", QString::number(std::chrono::duration_cast<std::chrono::seconds>(totalDuration).count()));
    toolTip += i18n("<br><b>Tokens:</b> %1", promptEvalTokenCount);
    return toolTip;
}

QString TextAutoGenerateTextReplyInfo::generateReplyTypeInfoOpenAI() const
{
    QString toolTip = i18n("<br><b>Token Count:</b> %1", tokenCount);
    toolTip += i18n("<br><b>Prompt Token:</b> %1", promptTokens);
    toolTip += i18n("<br><b>Completion Token:</b> %1", completionTokens);
    return toolTip;
}

QJsonObject TextAutoGenerateTextReplyInfo::serialize(const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &info)
{
    QJsonObject o;
    o["replyType"_L1] = TextAutoGenerateTextReplyInfo::convertReplyTypeToString(info.replyType);
    o["totalDuration"_L1] = static_cast<qint64>(info.totalDuration.count());
    o["loadDuration"_L1] = static_cast<qint64>(info.loadDuration.count());
    o["promptEvalTokenCount"_L1] = static_cast<qint64>(info.promptEvalTokenCount);
    o["promptEvalDuration"_L1] = static_cast<qint64>(info.promptEvalDuration.count());
    o["tokenCount"_L1] = static_cast<qint64>(info.tokenCount);
    o["completionTokens"_L1] = static_cast<qint64>(info.completionTokens);
    o["promptTokens"_L1] = static_cast<qint64>(info.promptTokens);
    o["duration"_L1] = static_cast<qint64>(info.duration.count());

    return o;
}

TextAutoGenerateText::TextAutoGenerateTextReplyInfo TextAutoGenerateTextReplyInfo::deserialize(const QJsonObject &o)
{
    TextAutoGenerateTextReplyInfo info;
    if (o.contains("replyType"_L1)) {
        const QString replyType = o["replyType"_L1].toString();
        if (!replyType.isEmpty()) {
            info.replyType = TextAutoGenerateTextReplyInfo::convertReplyTypeFromString(replyType);
            info.totalDuration = std::chrono::nanoseconds(o["totalDuration"_L1].toInteger());
            info.loadDuration = std::chrono::nanoseconds(o["loadDuration"_L1].toInteger());
            info.promptEvalTokenCount = o["promptEvalTokenCount"_L1].toInteger();
            info.promptEvalDuration = std::chrono::nanoseconds(o["promptEvalDuration"_L1].toInteger());
            info.tokenCount = o["tokenCount"_L1].toInteger();
            info.completionTokens = o["completionTokens"_L1].toInteger();
            info.promptTokens = o["promptTokens"_L1].toInteger();
            info.duration = std::chrono::nanoseconds(o["duration"_L1].toInteger());
        }
    }
    return info;
}

QString TextAutoGenerateTextReplyInfo::convertReplyTypeToString(TextAutoGenerateTextReplyInfo::ReplyType type)
{
    switch (type) {
    case ReplyType::Unknown:
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "convertReplyTypeToString: Invalid type. It's a bug";
        return {};
    case ReplyType::Ollama:
        return u"ollama"_s;
        break;
    case ReplyType::OpenAI:
        return u"openai"_s;
    }
    return {};
}

TextAutoGenerateTextReplyInfo::ReplyType TextAutoGenerateTextReplyInfo::convertReplyTypeFromString(const QString &str)
{
    if (str == "ollama"_L1) {
        return TextAutoGenerateTextReplyInfo::ReplyType::Ollama;
    } else if (str == "openai"_L1) {
        return TextAutoGenerateTextReplyInfo::ReplyType::OpenAI;
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "convertReplyTypeFromString: Invalid type. It's a bug";
        return TextAutoGenerateTextReplyInfo::ReplyType::Unknown;
    }
}
