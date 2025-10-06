/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateanswerinfo.h"
#include "textautogeneratetextcore_memory_debug.h"
#include <QJsonObject>
#include <qjsonarray.h>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAnswerInfo::TextAutoGenerateAnswerInfo()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAnswerInfo created " << this;
}

TextAutoGenerateAnswerInfo::~TextAutoGenerateAnswerInfo()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAnswerInfo deleted " << this;
}

TextAutoGenerateAnswerInfo::TextAutoGenerateAnswerInfo(const TextAutoGenerateAnswerInfo &other)
    : QSharedData(other)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAnswerInfo created " << this;
    mModelName = other.mModelName;
    mEngineName = other.mEngineName;
    mInstanceName = other.mInstanceName;
    mTools = other.mTools;
}

bool TextAutoGenerateAnswerInfo::isValid() const
{
    return !mModelName.isEmpty();
}

QString TextAutoGenerateAnswerInfo::modelName() const
{
    return mModelName;
}

void TextAutoGenerateAnswerInfo::setModelName(const QString &newModelName)
{
    mModelName = newModelName;
}

QString TextAutoGenerateAnswerInfo::engineName() const
{
    return mEngineName;
}

void TextAutoGenerateAnswerInfo::setEngineName(const QString &newEngineName)
{
    mEngineName = newEngineName;
}

QString TextAutoGenerateAnswerInfo::instanceName() const
{
    return mInstanceName;
}

void TextAutoGenerateAnswerInfo::setInstanceName(const QString &newInstanceName)
{
    mInstanceName = newInstanceName;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAnswerInfo &t)
{
    d.space() << "mInstanceName:" << t.instanceName();
    d.space() << "mModelName:" << t.modelName();
    d.space() << "mEngineName:" << t.engineName();
    d.space() << "mTools:" << t.tools();
    return d;
}

bool TextAutoGenerateAnswerInfo::operator==(const TextAutoGenerateAnswerInfo &other) const
{
    return mInstanceName == other.mInstanceName && mModelName == other.mModelName && mEngineName == other.mEngineName && mTools == other.mTools;
}

void TextAutoGenerateAnswerInfo::serialize(const TextAutoGenerateAnswerInfo &answerInfo, QJsonObject &o)
{
    o["modelName"_L1] = answerInfo.modelName();
    o["engineName"_L1] = answerInfo.engineName();
    o["instanceName"_L1] = answerInfo.instanceName();
    if (const auto answerTools = answerInfo.tools(); !answerTools.isEmpty()) {
        QJsonArray toolsArray;
        for (const QByteArray &b : answerTools) {
            toolsArray.append(QString::fromLatin1(b));
        }
        o["tools"_L1] = toolsArray;
    }
}

TextAutoGenerateAnswerInfo *TextAutoGenerateAnswerInfo::deserialize(const QJsonObject &o)
{
    TextAutoGenerateAnswerInfo *messageInfo = new TextAutoGenerateAnswerInfo;
    messageInfo->setModelName(o["modelName"_L1].toString());
    messageInfo->setEngineName(o["engineName"_L1].toString());
    messageInfo->setInstanceName(o["instanceName"_L1].toString());
    if (o.contains("tools"_L1)) {
        const QJsonArray toolsArray = o["tools"_L1].toArray();
        QList<QByteArray> lst;
        for (int i = 0; i < toolsArray.count(); i++) {
            lst.append(toolsArray[i].toString().toLatin1());
        }
        messageInfo->setTools(lst);
    }
    return messageInfo;
}

QList<QByteArray> TextAutoGenerateAnswerInfo::tools() const
{
    return mTools;
}

void TextAutoGenerateAnswerInfo::setTools(const QList<QByteArray> &newTools)
{
    mTools = newTools;
}
