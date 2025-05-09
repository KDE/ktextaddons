/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessage.h"
#include "core/textautogeneratemessageutils.h"

#include <QDateTime>
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
    QLocale locale;
    mDateTimeStr = locale.toString(QDateTime::fromSecsSinceEpoch(mDateTime));
}

bool TextAutoGenerateMessage::isValid() const
{
    return mSender != TextAutoGenerateMessage::Sender::Unknown;
}

bool TextAutoGenerateMessage::inProgress() const
{
    return mInProgress;
}

void TextAutoGenerateMessage::setInProgress(bool newInProgress)
{
    mInProgress = newInProgress;
}

bool TextAutoGenerateMessage::operator==(const TextAutoGenerateMessage &other) const
{
    return other.uuid() == mUuid && other.inProgress() == mInProgress && other.sender() == mSender && other.dateTime() == mDateTime
        && other.content() == mContent && other.answerUuid() == mAnswerUuid && other.editingMode() == mEditingMode && other.modelName() == mModelName
        && other.engineName() == mEngineName && other.context() == mContext;
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
    return mMouseHover;
}

void TextAutoGenerateMessage::setMouseHover(bool newMouseHover)
{
    mMouseHover = newMouseHover;
}

bool TextAutoGenerateMessage::editingMode() const
{
    return mEditingMode;
}

void TextAutoGenerateMessage::setEditingMode(bool newEditingMode)
{
    mEditingMode = newEditingMode;
}

QString TextAutoGenerateMessage::modelName() const
{
    return mModelName;
}

void TextAutoGenerateMessage::setModelName(const QString &newModelName)
{
    mModelName = newModelName;
}

QString TextAutoGenerateMessage::engineName() const
{
    return mEngineName;
}

void TextAutoGenerateMessage::setEngineName(const QString &newEngineName)
{
    mEngineName = newEngineName;
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
        return QStringLiteral("user");
    case Sender::LLM:
        return QStringLiteral("llm");
    }
    Q_UNREACHABLE();
}

TextAutoGenerateMessage::Sender TextAutoGenerateMessage::senderFromString(const QString &str)
{
    if (str == "user"_L1) {
        return TextAutoGenerateMessage::Sender::User;
    } else if (str == "llm"_L1) {
        return TextAutoGenerateMessage::Sender::LLM;
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
    o["modelName"_L1] = msg.mModelName;
    o["engineName"_L1] = msg.mEngineName;
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
    msg.setDateTime(o["dateTime"_L1].toInteger());
    msg.setSender(senderFromString(o["sender"_L1].toString()));
    return msg;
}

#include "moc_textautogeneratemessage.cpp"
