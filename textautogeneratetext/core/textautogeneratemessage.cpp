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
    d.space() << "engineName:" << t.engineName();
    d.space() << "modelName:" << t.modelName();
    d.space() << "context:" << t.context();
    return d;
}

QString TextAutoGenerateMessage::content() const
{
    return mContent;
}

void TextAutoGenerateMessage::setContent(const QString &newContent)
{
    if (mContent != newContent) {
        mContent = newContent;
        mHtmlGenerated = TextAutoGenerateMessageUtils::convertTextToHtml(mContent);
    }
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
    return other.uuid() == mUuid && other.inProgress() == inProgress() && other.sender() == mSender && other.dateTime() == mDateTime
        && other.content() == mContent && other.answerUuid() == mAnswerUuid && other.editingMode() == editingMode() && other.modelName() == modelName()
        && other.engineName() == engineName() && other.context() == mContext;
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

void TextAutoGenerateMessage::setInstanceName(const QString &instanceName)
{
    answerInfo()->setInstanceName(instanceName);
}

QString TextAutoGenerateMessage::instanceName() const
{
    if (mMessageInfo) {
        return mMessageInfo->instanceName();
    }
    return {};
}

void TextAutoGenerateMessage::setModelName(const QString &newModelName)
{
    answerInfo()->setModelName(newModelName);
}

QString TextAutoGenerateMessage::engineName() const
{
    if (mMessageInfo) {
        return mMessageInfo->engineName();
    }
    return {};
}

void TextAutoGenerateMessage::setEngineName(const QString &newEngineName)
{
    answerInfo()->setEngineName(newEngineName);
}

TextAutoGenerateTextContext TextAutoGenerateMessage::context() const
{
    return mContext;
}

void TextAutoGenerateMessage::setContext(const TextAutoGenerateText::TextAutoGenerateTextContext &newContext)
{
    mContext = newContext;
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
        o["modelName"_L1] = msg.modelName();
        o["engineName"_L1] = msg.engineName();
        o["instanceName"_L1] = msg.instanceName();
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
    msg.setModelName(o["modelName"_L1].toString());
    msg.setEngineName(o["engineName"_L1].toString());
    msg.setInstanceName(o["instanceName"_L1].toString());
    msg.setDateTime(o["dateTime"_L1].toInteger());
    msg.setSender(senderFromString(o["sender"_L1].toString()));
    return msg;
}

TextAutoGenerateAnswerInfo *TextAutoGenerateMessage::answerInfo()
{
    if (!mMessageInfo) {
        mMessageInfo = new TextAutoGenerateAnswerInfo;
    }
    return mMessageInfo;
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
