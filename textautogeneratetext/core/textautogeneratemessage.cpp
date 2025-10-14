/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessage.h"
#include "textautogenerateanswerinfo.h"
#include "textautogeneratemessageutils.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateMessage::TextAutoGenerateMessage() = default;

TextAutoGenerateMessage::~TextAutoGenerateMessage() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateMessage &t)
{
    d.space() << "content:" << t.content();
    d.space() << "htmlGenerated:" << t.htmlGenerated();
    d.space() << "sender:" << t.sender();
    d.space() << "dateTime:" << t.dateTime();
    d.space() << "in progress:" << t.inProgress();
    d.space() << "uuid:" << t.uuid();
    d.space() << "answerUuid:" << t.answerUuid();
    d.space() << "mouseHover:" << t.mouseHover();
    d.space() << "editingMode:" << t.editingMode();
    if (t.messageInfo()) {
        d.space() << "message Info:" << *t.messageInfo();
    }
    if (t.messageAttachment()) {
        d.space() << "Message Attachment:" << *t.messageAttachment();
    }

    return d;
}

QString TextAutoGenerateMessage::content() const
{
    return mContent;
}

void TextAutoGenerateMessage::generateHtml(const QString &searchText, int hightLightStringIndex)
{
    int numberOfTextSearched = 0;
    mHtmlGenerated = TextAutoGenerateMessageUtils::convertTextToHtml(mContent, mUuid, searchText, numberOfTextSearched, hightLightStringIndex);
    mNumberOfTextSearched = numberOfTextSearched;
}

void TextAutoGenerateMessage::setContent(const QString &newContent)
{
    mContent = newContent;
}

TextAutoGenerateMessage::Sender TextAutoGenerateMessage::sender() const
{
    return mSender;
}

void TextAutoGenerateMessage::setSender(TextAutoGenerateMessage::Sender newSender)
{
    mSender = newSender;
}

qint64 TextAutoGenerateMessage::dateTime() const
{
    return mDateTime;
}

void TextAutoGenerateMessage::setDateTime(qint64 newDateTime)
{
    mDateTime = newDateTime;
    const QLocale locale;
    mDateTimeStr = locale.toString(QDateTime::fromSecsSinceEpoch(mDateTime));
}

bool TextAutoGenerateMessage::isValid() const
{
    return mSender != TextAutoGenerateMessage::Sender::Unknown;
}

bool TextAutoGenerateMessage::inProgress() const
{
    return messageStateValue(MessageState::InProgress);
}

void TextAutoGenerateMessage::setInProgress(bool newInProgress)
{
    assignMessageStateValue(MessageState::InProgress, newInProgress);
}

bool TextAutoGenerateMessage::operator==(const TextAutoGenerateMessage &other) const
{
    bool result = other.uuid() == mUuid && other.inProgress() == inProgress() && other.sender() == mSender && other.dateTime() == mDateTime
        && other.content() == mContent && other.answerUuid() == mAnswerUuid && other.editingMode() == editingMode();
    if (!result) {
        return false;
    }
    if (messageInfo() && other.messageInfo()) {
        if (*messageInfo() == (*other.messageInfo())) {
            result = true;
        } else {
            return false;
        }
    } else if (!messageInfo() && !other.messageInfo()) {
        result = true;
    } else {
        return false;
    }
    if (messageAttachment() && other.messageAttachment()) {
        if (*messageAttachment() == (*other.messageAttachment())) {
            result = true;
        } else {
            return false;
        }
    } else if (!messageAttachment() && !other.messageAttachment()) {
        result = true;
    } else {
        return false;
    }

    return result;
}

QByteArray TextAutoGenerateMessage::uuid() const
{
    return mUuid;
}

void TextAutoGenerateMessage::setUuid(const QByteArray &newUuid)
{
    mUuid = newUuid;
}

QString TextAutoGenerateMessage::htmlGenerated() const
{
    return mHtmlGenerated;
}

QByteArray TextAutoGenerateMessage::answerUuid() const
{
    return mAnswerUuid;
}

void TextAutoGenerateMessage::setAnswerUuid(const QByteArray &newAnswerUuid)
{
    mAnswerUuid = newAnswerUuid;
}

QString TextAutoGenerateMessage::dateTimeStr() const
{
    return mDateTimeStr;
}

bool TextAutoGenerateMessage::mouseHover() const
{
    return messageStateValue(MessageState::HoverHighlight);
}

void TextAutoGenerateMessage::setMouseHover(bool newMouseHover)
{
    assignMessageStateValue(MessageState::HoverHighlight, newMouseHover);
}

bool TextAutoGenerateMessage::editingMode() const
{
    return messageStateValue(MessageState::Edited);
}

void TextAutoGenerateMessage::setEditingMode(bool newEditingMode)
{
    assignMessageStateValue(MessageState::Edited, newEditingMode);
}

QString TextAutoGenerateMessage::modelName() const
{
    if (mMessageInfo) {
        return mMessageInfo->modelName();
    }
    return {};
}

const TextAutoGenerateAnswerInfo *TextAutoGenerateMessage::messageInfo() const
{
    if (mMessageInfo) {
        return mMessageInfo.data();
    }
    return nullptr;
}

QList<QByteArray> TextAutoGenerateMessage::tools() const
{
    if (mMessageInfo) {
        return mMessageInfo->tools();
    }
    return {};
}

QString TextAutoGenerateMessage::instanceName() const
{
    if (mMessageInfo) {
        return mMessageInfo->instanceName();
    }
    return {};
}

QString TextAutoGenerateMessage::engineName() const
{
    if (mMessageInfo) {
        return mMessageInfo->engineName();
    }
    return {};
}

void TextAutoGenerateMessage::setMessageInfo(const TextAutoGenerateAnswerInfo &messageInfo)
{
    if (!mMessageInfo) {
        mMessageInfo = new TextAutoGenerateAnswerInfo(messageInfo);
    } else {
        mMessageInfo.reset(new TextAutoGenerateAnswerInfo(messageInfo));
    }
}

QString TextAutoGenerateMessage::senderToString() const
{
    switch (mSender) {
    case Sender::Unknown:
        return {};
    case Sender::User:
        return u"user"_s;
    case Sender::Assistant:
        return u"llm"_s;
    case Sender::System:
        return u"system"_s;
    case Sender::Tool:
        return u"tool"_s;
    }
    Q_UNREACHABLE();
}

TextAutoGenerateMessage::Sender TextAutoGenerateMessage::senderFromString(const QString &str)
{
    if (str == "user"_L1) {
        return TextAutoGenerateMessage::Sender::User;
    } else if (str == "llm"_L1) {
        return TextAutoGenerateMessage::Sender::Assistant;
    } else if (str == "system"_L1) {
        return TextAutoGenerateMessage::Sender::System;
    } else if (str == "tool"_L1) {
        return TextAutoGenerateMessage::Sender::Tool;
    } else {
        return TextAutoGenerateMessage::Sender::Unknown;
    }
}

QByteArray TextAutoGenerateMessage::serialize(const TextAutoGenerateMessage &msg, bool toBinary)
{
    QJsonDocument d;
    QJsonObject o;
    o["identifier"_L1] = QString::fromLatin1(msg.mUuid);
    o["answerIdentifier"_L1] = QString::fromLatin1(msg.mAnswerUuid);
    o["text"_L1] = msg.mContent;
    if (msg.sender() != Sender::User) {
        if (auto info = msg.messageInfo(); info) {
            TextAutoGenerateAnswerInfo::serialize(*info, o);
        }
    }
    if (auto att = msg.messageAttachment(); att) {
        TextAutoGenerateAttachment::serialize(*att, o);
    }
    o["sender"_L1] = msg.senderToString();
    o["dateTime"_L1] = msg.mDateTime;
    if (toBinary) {
        return QCborValue::fromJsonValue(o).toCbor();
    }
    d.setObject(o);
    return d.toJson(QJsonDocument::Indented);
}

TextAutoGenerateMessage TextAutoGenerateMessage::deserialize(const QJsonObject &o)
{
    TextAutoGenerateMessage msg;

    msg.setUuid(o["identifier"_L1].toString().toLatin1());
    msg.setAnswerUuid(o["answerIdentifier"_L1].toString().toLatin1());
    msg.setContent(o["text"_L1].toString());
    msg.generateHtml();

    TextAutoGenerateAnswerInfo *messageInfoDeserialized = TextAutoGenerateAnswerInfo::deserialize(o);
    if (messageInfoDeserialized->isValid()) {
        msg.setMessageInfo(*messageInfoDeserialized);
    }
    delete messageInfoDeserialized;

    TextAutoGenerateAttachment *attDeserialized = TextAutoGenerateAttachment::deserialize(o);
    if (attDeserialized->isValid()) {
        msg.setMessageAttachment(*attDeserialized);
    }
    delete attDeserialized;

    msg.setDateTime(o["dateTime"_L1].toInteger());
    msg.setSender(senderFromString(o["sender"_L1].toString()));
    return msg;
}

QJsonObject TextAutoGenerateMessage::convertToOllamaChatJson() const
{
    QJsonObject obj;
    if (mContent.isEmpty()) {
        return obj;
    }
    QString role;
    switch (mSender) {
    case Sender::Unknown:
        break;
    case Sender::User:
        role = u"user"_s;
        break;
    case Sender::Assistant:
        role = u"assistant"_s;
        break;
    case Sender::System:
        role = u"system"_s;
        break;
    case Sender::Tool:
        role = u"tool"_s;
        break;
    }
    if (role.isEmpty()) {
        return obj;
    }
    obj["role"_L1] = role;
    obj["content"_L1] = mContent;
    return obj;
}

bool TextAutoGenerateMessage::messageStateValue(MessageState type) const
{
    return mMessageStates & type;
}

int TextAutoGenerateMessage::numberOfTextSearched() const
{
    return mNumberOfTextSearched;
}

const TextAutoGenerateAttachment *TextAutoGenerateMessage::messageAttachment() const
{
    if (mMessageAttachment) {
        return mMessageAttachment.data();
    }
    return nullptr;
}

void TextAutoGenerateMessage::setMessageAttachment(const TextAutoGenerateAttachment &newMessageAttachment)
{
    if (!mMessageAttachment) {
        mMessageAttachment = new TextAutoGenerateAttachment(newMessageAttachment);
    } else {
        mMessageAttachment.reset(new TextAutoGenerateAttachment(newMessageAttachment));
    }
}

TextAutoGenerateMessage::MessageStates TextAutoGenerateMessage::messageStates() const
{
    return mMessageStates;
}

void TextAutoGenerateMessage::setMessageStates(const MessageStates &newMessageStates)
{
    mMessageStates = newMessageStates;
}

void TextAutoGenerateMessage::assignMessageStateValue(MessageState type, bool status)
{
    if (status) {
        mMessageStates |= type;
    } else {
        mMessageStates &= ~type;
    }
}
#include "moc_textautogeneratemessage.cpp"
