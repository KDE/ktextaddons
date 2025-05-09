/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocalmessagesdatabase.h"
#include "textautogeneratelocaldatabaseutils.h"
#include "textautogeneratetextcore_database_debug.h"
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static const char s_schemaMessagesDataBase[] = "CREATE TABLE MESSAGES (messageId TEXT PRIMARY KEY NOT NULL, json TEXT)";
enum class MessagesFields {
    MessageId,
    Json,
}; // in the same order as the table
using namespace TextAutoGenerateText;
TextAutoGenerateLocalMessagesDatabase::TextAutoGenerateLocalMessagesDatabase()
    : TextAutoGenerateLocalDatabaseAbstract(TextAutoGenerateLocalDatabaseUtils::localMessagesDatabasePath(),
                                            TextAutoGenerateLocalMessagesDatabase::DatabaseType::Messages)
{
}

TextAutoGenerateLocalMessagesDatabase::~TextAutoGenerateLocalMessagesDatabase() = default;

void TextAutoGenerateLocalMessagesDatabase::deleteMessage(const QString &chatIdentifier, const QString &messageId)
{
    QSqlDatabase db;
    if (!checkDataBase(chatIdentifier, db)) {
        return;
    }
    QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::deleteMessage(), db);
    query.addBindValue(messageId);
    if (!query.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in MESSAGES table" << db.databaseName() << query.lastError();
    }
}

void TextAutoGenerateLocalMessagesDatabase::addMessage(const QString &chatIdentifier, const TextAutoGenerateMessage &m)
{
    QSqlDatabase db;
    if (initializeDataBase(chatIdentifier, db)) {
        QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::insertReplaceMessage(), db);
        query.addBindValue(QString::fromLatin1(m.uuid()));
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
    model->select();
    return model;
}
