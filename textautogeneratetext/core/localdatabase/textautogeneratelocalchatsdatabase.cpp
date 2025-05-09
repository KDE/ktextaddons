/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocalchatsdatabase.h"
#include "textautogeneratelocaldatabaseutils.h"
#include "textautogeneratetextcore_database_debug.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

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
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in ROOMS table" << db.databaseName() << query.lastError();
        }
    }
}

void TextAutoGenerateLocalChatsDatabase::deleteChat(const QString &chatId)
{
    QSqlDatabase db;
    if (!checkDataBase(QString(), db)) {
        return;
    }
    QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::deleteChat(), db);
    query.addBindValue(chatId);
    if (!query.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in ROOMS table" << db.databaseName() << query.lastError();
    }
}
