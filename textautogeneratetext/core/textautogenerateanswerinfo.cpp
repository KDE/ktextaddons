/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateanswerinfo.h"
#include "textautogeneratetextcore_memory_debug.h"

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
    return d;
}

bool TextAutoGenerateAnswerInfo::operator==(const TextAutoGenerateAnswerInfo &other) const
{
    return mInstanceName == other.mInstanceName && mModelName == other.mModelName && mEngineName == other.mEngineName;
}
