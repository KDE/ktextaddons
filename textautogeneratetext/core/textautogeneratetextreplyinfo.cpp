/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextreplyinfo.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
#include <QDebug>
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
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid type. It's a bug";
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

QByteArray serialize(const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &info, bool toBinary)
{
    QJsonDocument d;
    QJsonObject o;

    if (toBinary) {
        return QCborValue::fromJsonValue(o).toCbor();
    }
    d.setObject(o);
    return d.toJson(QJsonDocument::Indented);
}

TextAutoGenerateText::TextAutoGenerateTextReplyInfo deserialize(const QJsonObject &o)
{
    TextAutoGenerateTextReplyInfo info;

    return info;
}
