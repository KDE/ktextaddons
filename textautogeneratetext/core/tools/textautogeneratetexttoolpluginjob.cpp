/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginjob.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolPluginJob::TextAutoGenerateTextToolPluginJob(QObject *parent)
    : TextAutoGenerateTextToolBaseJob{parent}
{
}

TextAutoGenerateTextToolPluginJob::~TextAutoGenerateTextToolPluginJob() = default;

void TextAutoGenerateTextToolPluginJob::start()
{
    Q_ASSERT(false);
}

void TextAutoGenerateTextToolPluginJob::setProperties(const QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> &newProperties)
{
    mProperties = newProperties;
}

QList<TextAutoGenerateTextToolPluginProperty> TextAutoGenerateTextToolPluginJob::properties() const
{
    return mProperties;
}

bool TextAutoGenerateTextToolPluginJob::verifyRequiredArguments() const
{
    const QStringList requiredArgs = required();
    if (mToolArguments.isEmpty() || requiredArgs.isEmpty()) {
        return false;
    }
    if (requiredArgs.count() > mToolArguments.count()) {
        return false;
    }
    for (const auto &arg : requiredArgs) {
        bool found = false;
        for (const auto &tools : mToolArguments) {
            if (tools.keyTool == arg) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolPluginJob &t)
{
    d.space() << "toolArguments" << t.toolArguments();
    d.space() << "messageUuid" << t.messageUuid();
    d.space() << "chatId" << t.chatId();
    d.space() << "toolIdentifier" << t.toolIdentifier();
    d.space() << "properties" << t.properties();
    return d;
}

#include "moc_textautogeneratetexttoolpluginjob.cpp"
