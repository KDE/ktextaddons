/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocalmessagesdatabase.h"
#include "core/textautogeneratesearchmessageutils.h"
#include "textautogeneratelocaldatabaseutils.h"
#include "textautogeneratetextcore_database_debug.h"
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static const char s_schemaMessagesDataBase[] = "CREATE TABLE MESSAGES (messageId TEXT PRIMARY KEY NOT NULL, timestamp INTEGER, json TEXT)";
enum class MessagesFields {
    MessageId,
    TimeStamp,
    Json,
}; // in the same order as the table
using namespace TextAutoGenerateText;
TextAutoGenerateLocalMessagesDatabase::TextAutoGenerateLocalMessagesDatabase()
    : TextAutoGenerateLocalDatabaseAbstract(TextAutoGenerateLocalDatabaseUtils::localMessagesDatabasePath(),
                                            TextAutoGenerateLocalMessagesDatabase::DatabaseType::Messages)
{
}

TextAutoGenerateLocalMessagesDatabase::~TextAutoGenerateLocalMessagesDatabase() = default;

void TextAutoGenerateLocalMessagesDatabase::deleteDatabase(const QByteArray &chatIdentifier)
{
    const QString chatId = QString::fromLatin1(chatIdentifier);
    QSqlDatabase db;
    if (!checkDataBase(chatId, db)) {
        return;
    }
    const QString dbName = generateDbName(chatId);
    QSqlDatabase::removeDatabase(dbName);
    const QString path = dbFileName(chatId);
    if (!QFile(path).remove()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Impossible to remove file" << path;
    }
}

void TextAutoGenerateLocalMessagesDatabase::deleteMessage(const QByteArray &chatIdentifier, const QString &messageId)
{
    QSqlDatabase db;
    if (!checkDataBase(QString::fromLatin1(chatIdentifier), db)) {
        return;
    }
    QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::deleteMessage(), db);
    query.addBindValue(messageId);
    if (!query.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in MESSAGES table" << db.databaseName() << query.lastError();
    }
}

void TextAutoGenerateLocalMessagesDatabase::insertOrReplaceMessage(const QByteArray &chatIdentifier, const TextAutoGenerateMessage &m)
{
    QSqlDatabase db;
    if (initializeDataBase(QString::fromLatin1(chatIdentifier), db)) {
        QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::insertReplaceMessage(), db);
        query.addBindValue(QString::fromLatin1(m.uuid()));
        query.addBindValue(m.dateTime());
        // qDebug() << " m.timeStamp() " << m.timeStamp();
        // FIXME look at why we can't save a binary ?
        query.addBindValue(TextAutoGenerateMessage::serialize(m, false)); // TODO binary or not ?
        if (!query.exec()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in MESSAGES table" << db.databaseName() << query.lastError();
        }
    }
}

QString TextAutoGenerateLocalMessagesDatabase::schemaDataBase() const
{
    return QString::fromLatin1(s_schemaMessagesDataBase);
}

std::unique_ptr<QSqlTableModel> TextAutoGenerateLocalMessagesDatabase::createMessageModel(const QString &chatIdentifier) const
{
    const QString dbName = generateDbName(chatIdentifier);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    if (!db.isValid()) {
        // Open the DB if it exists (don't create a new one)
        const QString fileName = dbFileName(chatIdentifier);
        // qDebug() << " fileName " << fileName;
        if (!QFileInfo::exists(fileName)) {
            return {};
        }
        db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), dbName);
        db.setDatabaseName(fileName);
        if (!db.open()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't open" << fileName;
            return {};
        }
    }

    Q_ASSERT(db.isValid());
    Q_ASSERT(db.isOpen());
    auto model = std::make_unique<QSqlTableModel>(nullptr, db);
    model->setTable(QStringLiteral("MESSAGES"));
    model->setSort(int(MessagesFields::TimeStamp), Qt::AscendingOrder);
    model->select();
    return model;
}

QString TextAutoGenerateLocalMessagesDatabase::generateQueryStr()
{
    QString query = QStringLiteral("SELECT * FROM MESSAGES");
    query += QStringLiteral(" ORDER BY timestamp DESC");
    return query;
}

QList<TextAutoGenerateMessage> TextAutoGenerateLocalMessagesDatabase::loadMessages(const QString &chatIdentifier) const
{
    const QString dbName = generateDbName(chatIdentifier);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    if (!db.isValid()) {
        // Open the DB if it exists (don't create a new one)
        const QString fileName = dbFileName(chatIdentifier);
        // qDebug() << " fileName " << fileName;
        if (!QFileInfo::exists(fileName)) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Filename doesn't exist: " << fileName;
            return {};
        }
        db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), dbName);
        db.setDatabaseName(fileName);
        if (!db.open()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't open" << fileName;
            return {};
        }
    }

    Q_ASSERT(db.isValid());
    Q_ASSERT(db.isOpen());
    const QString query = TextAutoGenerateLocalMessagesDatabase::generateQueryStr();
    QSqlQuery resultQuery(db);
    resultQuery.prepare(query);
    if (!resultQuery.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << " Impossible to execute query: " << resultQuery.lastError() << " query: " << query;
        return {};
    }

    QList<TextAutoGenerateMessage> listMessages;
    while (resultQuery.next()) {
        const QString json = resultQuery.value(QStringLiteral("json")).toString();
        listMessages.append(convertJsonToMessage(json));
    }
    return listMessages;
}

QList<TextAutoGenerateSearchMessage> TextAutoGenerateLocalMessagesDatabase::searchMessages(const QString &chatIdentifier, const QString &searchText) const
{
    const QString dbName = generateDbName(chatIdentifier);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    if (!db.isValid()) {
        // Open the DB if it exists (don't create a new one)
        const QString fileName = dbFileName(chatIdentifier);
        // qDebug() << " fileName " << fileName;
        if (!QFileInfo::exists(fileName)) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Filename doesn't exist: " << fileName;
            return {};
        }
        db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), dbName);
        db.setDatabaseName(fileName);
        if (!db.open()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't open" << fileName;
            return {};
        }
    }

    Q_ASSERT(db.isValid());
    Q_ASSERT(db.isOpen());
    const QString query = TextAutoGenerateLocalMessagesDatabase::generateQueryStr();
    QSqlQuery resultQuery(db);
    resultQuery.prepare(query);
    if (!resultQuery.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << " Impossible to execute query: " << resultQuery.lastError() << " query: " << query;
        return {};
    }
    QList<TextAutoGenerateSearchMessage> lstSearchMessages;
    while (resultQuery.next()) {
        const QString json = resultQuery.value(QStringLiteral("json")).toString();
        const TextAutoGenerateMessage msg = convertJsonToMessage(json);
        if (msg.content().contains(searchText, Qt::CaseInsensitive)) {
            TextAutoGenerateSearchMessage searchMessage;
            searchMessage.setMessageId(msg.uuid());
            searchMessage.setChatId(chatIdentifier.toLatin1());
            searchMessage.setDateTime(msg.dateTime());
            searchMessage.setPreviewText(TextAutoGenerateSearchMessageUtils::generatePreview(msg.content()));
            lstSearchMessages.append(searchMessage);
        }
    }
    return lstSearchMessages;
}

TextAutoGenerateMessage TextAutoGenerateLocalMessagesDatabase::convertJsonToMessage(const QString &json) const
{
    const QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    const TextAutoGenerateMessage msg = TextAutoGenerateMessage::deserialize(doc.object());
    return msg;
}
