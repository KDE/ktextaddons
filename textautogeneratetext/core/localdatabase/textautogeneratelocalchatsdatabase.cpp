/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocalchatsdatabase.h"

#include "textautogeneratelocaldatabaseutils.h"
#include "textautogeneratetextcore_database_debug.h"
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

using namespace Qt::Literals::StringLiterals;
static const char s_schemaChatsDataBase[] = "CREATE TABLE CHATS (chatId TEXT PRIMARY KEY NOT NULL, json TEXT)";
enum class ChatsFields {
    ChatId,
    Json,
}; // in the same order as the table

using namespace TextAutoGenerateText;
TextAutoGenerateLocalChatsDatabase::TextAutoGenerateLocalChatsDatabase()
    : TextAutoGenerateLocalDatabaseAbstract(TextAutoGenerateLocalDatabaseUtils::localChatsDatabasePath(),
                                            TextAutoGenerateLocalChatsDatabase::DatabaseType::Chats)
{
}

TextAutoGenerateLocalChatsDatabase::~TextAutoGenerateLocalChatsDatabase() = default;

std::unique_ptr<QSqlTableModel> TextAutoGenerateLocalChatsDatabase::createChatsModel() const
{
    const QString dbName = generateDbName({});
    QSqlDatabase db = QSqlDatabase::database(dbName);
    if (!db.isValid()) {
        // Open the DB if it exists (don't create a new one)
        const QString fileName = dbFileName({});
        // qDebug() << " fileName " << fileName;
        if (!QFileInfo::exists(fileName)) {
            return {};
        }
        db = QSqlDatabase::addDatabase(u"QSQLITE"_s, dbName);
        db.setDatabaseName(fileName);
        if (!db.open()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't open" << fileName;
            return {};
        }
    }

    Q_ASSERT(db.isValid());
    Q_ASSERT(db.isOpen());
    auto model = std::make_unique<QSqlTableModel>(nullptr, db);
    model->setTable(u"CHATS"_s);
    // model->setSort(int(MessagesFields::TimeStamp), Qt::AscendingOrder);
    model->select();
    return model;
}

QString TextAutoGenerateLocalChatsDatabase::schemaDataBase() const
{
    return QString::fromLatin1(s_schemaChatsDataBase);
}

void TextAutoGenerateLocalChatsDatabase::insertOrUpdateChat(const TextAutoGenerateChat &chat)
{
    QSqlDatabase db;
    if (initializeDataBase(QString(), db)) {
        QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::insertReplaceChat(), db);
        query.addBindValue(QString::fromLatin1(chat.identifier()));
        query.addBindValue(TextAutoGenerateChat::serialize(chat, false)); // TODO use binary ?
        if (!query.exec()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in CHATS table" << db.databaseName() << query.lastError();
        }
    }
}

QList<TextAutoGenerateChat> TextAutoGenerateLocalChatsDatabase::loadChats() const
{
    const QString dbName = generateDbName(QString());
    QSqlDatabase db = QSqlDatabase::database(dbName);
    if (!db.isValid()) {
        // Open the DB if it exists (don't create a new one)
        const QString fileName = dbFileName(QString());
        // qDebug() << " fileName " << fileName;
        if (!QFileInfo::exists(fileName)) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Filename doesn't exist: " << fileName;
            return {};
        }
        db = QSqlDatabase::addDatabase(u"QSQLITE"_s, dbName);
        db.setDatabaseName(fileName);
        if (!db.open()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't open" << fileName;
            return {};
        }
    }

    Q_ASSERT(db.isValid());
    Q_ASSERT(db.isOpen());
    const QString query = TextAutoGenerateLocalChatsDatabase::generateQueryStr();
    QSqlQuery resultQuery(db);
    resultQuery.prepare(query);
    if (!resultQuery.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << " Impossible to execute query: " << resultQuery.lastError() << " query: " << query;
        return {};
    }

    QList<TextAutoGenerateChat> listChats;
    while (resultQuery.next()) {
        const QString json = resultQuery.value(u"json"_s).toString();
        listChats.append(convertJsonToMessage(json));
    }
    return listChats;
}

TextAutoGenerateChat TextAutoGenerateLocalChatsDatabase::convertJsonToMessage(const QString &json) const
{
    const QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    const TextAutoGenerateChat msg = TextAutoGenerateChat::deserialize(doc.object());
    return msg;
}

QString TextAutoGenerateLocalChatsDatabase::generateQueryStr()
{
    const QString query = u"SELECT * FROM CHATS"_s;
    return query;
}

void TextAutoGenerateLocalChatsDatabase::deleteChat(const QByteArray &chatId)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "deleteChat" << chatId;
    QSqlDatabase db;
    if (!checkDataBase(QString(), db)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Problem when check checkDataBase" << chatId;
        return;
    }
    QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::deleteChat(), db);
    query.addBindValue(QString::fromLatin1(chatId));
    if (!query.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in CHATS table" << db.databaseName() << query.lastError();
    }
}
