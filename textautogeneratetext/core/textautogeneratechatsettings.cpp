/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsettings.h"
#include "core/localdatabase/textautogeneratelocaldatabasemanager.h"
#include "core/textautogeneratemanager.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateChatSettings::TextAutoGenerateChatSettings(TextAutoGenerateManager *manager)
    : mManager(manager)
{
}

TextAutoGenerateChatSettings::~TextAutoGenerateChatSettings() = default;

void TextAutoGenerateChatSettings::remove(const QByteArray &chatId)
{
    if (mPendingTypedTexts.remove(chatId) > 0) {
        if (mManager) {
            mManager->databaseManager()->deleteRoomPendingTypedInfo(chatId);
        }
    }
}

void TextAutoGenerateChatSettings::add(const QByteArray &chatId, const PendingTypedInfo &info)
{
    mPendingTypedTexts[chatId] = info;
    if (mManager) {
        mManager->databaseManager()->updateRoomPendingTypedInfo(chatId, info);
    }
}

bool TextAutoGenerateChatSettings::hasPendingMessageTyped(const QByteArray &chatId) const
{
    return mPendingTypedTexts.value(chatId).hasPendingMessageTyped();
}

TextAutoGenerateChatSettings::PendingTypedInfo TextAutoGenerateChatSettings::value(const QByteArray &chatId)
{
    const auto pending = mPendingTypedTexts.take(chatId);
    if (pending.isValid()) {
        if (mManager) {
            mManager->databaseManager()->deleteRoomPendingTypedInfo(chatId);
        }
    }
    return pending;
}

bool TextAutoGenerateChatSettings::isEmpty() const
{
    return mPendingTypedTexts.isEmpty();
}

int TextAutoGenerateChatSettings::count() const
{
    return mPendingTypedTexts.count();
}

bool TextAutoGenerateChatSettings::PendingTypedInfo::isValid() const
{
    return !text.isEmpty() || (scrollbarPosition != -1) || !tools.isEmpty();
}

bool TextAutoGenerateChatSettings::PendingTypedInfo::hasPendingMessageTyped() const
{
    return !text.isEmpty();
}

QDebug operator<<(QDebug d, const TextAutoGenerateChatSettings::PendingTypedInfo &t)
{
    d.space() << "text" << t.text;
    d.space() << "scrollbarPosition" << t.scrollbarPosition;
    d.space() << "tools" << t.tools;
    return d;
}

bool TextAutoGenerateChatSettings::PendingTypedInfo::operator==(const TextAutoGenerateChatSettings::PendingTypedInfo &other) const
{
    return text == other.text && scrollbarPosition == other.scrollbarPosition && tools == other.tools;
}

QJsonObject TextAutoGenerateChatSettings::PendingTypedInfo::serialize(const TextAutoGenerateChatSettings::PendingTypedInfo &pendingTypedInfo)
{
    QJsonObject obj;
    if (!pendingTypedInfo.text.isEmpty()) {
        obj["text"_L1] = pendingTypedInfo.text;
    }
    if (pendingTypedInfo.scrollbarPosition != -1) {
        obj["scrollbarPosition"_L1] = pendingTypedInfo.scrollbarPosition;
    }
    if (!pendingTypedInfo.tools.isEmpty()) {
        QJsonArray toolsArray;
        for (const QByteArray &ba : std::as_const(pendingTypedInfo.tools)) {
            toolsArray.append(QString::fromLatin1(ba));
        }
        obj["tools"_L1] = toolsArray;
    }
    return obj;
}

TextAutoGenerateChatSettings::PendingTypedInfo TextAutoGenerateChatSettings::PendingTypedInfo::deserialize(const QJsonObject &o)
{
    TextAutoGenerateChatSettings::PendingTypedInfo pendingTypedInfo;
    pendingTypedInfo.text = o.value("text"_L1).toString();
    pendingTypedInfo.scrollbarPosition = o.value("scrollbarPosition"_L1).toInt(-1);
    const QJsonArray toolsArray = o.value("tools"_L1).toArray();
    QList<QByteArray> tools;
    for (const auto &val : toolsArray) {
        tools.append(val.toString().toLatin1());
    }
    pendingTypedInfo.tools = tools;
    return pendingTypedInfo;
}

void TextAutoGenerateChatSettings::loadRoomPendingTypedInfo()
{
    setPendingTypedTexts(mManager->databaseManager()->loadRoomPendingTypedInfo());
}

void TextAutoGenerateChatSettings::setPendingTypedTexts(const QMap<QByteArray, TextAutoGenerateChatSettings::PendingTypedInfo> &newPendingTypedTexts)
{
    mPendingTypedTexts = newPendingTypedTexts;
}
