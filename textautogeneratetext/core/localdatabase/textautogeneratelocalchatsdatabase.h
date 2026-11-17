/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextcore_export.h"
#include <TextAutoGenerateText/TextAutoGenerateChat>
#include <TextAutoGenerateText/TextAutoGenerateLocalDatabaseAbstract>
#include <memory>
class QSqlTableModel;

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXTCORE_EXPORT TextAutoGenerateLocalChatsDatabase : public TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalChatsDatabase();
    ~TextAutoGenerateLocalChatsDatabase() override;

    void deleteChat(const QByteArray &chatId);
    void insertOrUpdateChat(const TextAutoGenerateChat &chat);

    [[nodiscard]] QList<TextAutoGenerateChat> loadChats() const;
    [[nodiscard]] std::unique_ptr<QSqlTableModel> createChatsModel() const;

protected:
    [[nodiscard]] QString schemaDataBase() const override;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXTCORE_NO_EXPORT static QString generateQueryStr();
    [[nodiscard]] TEXTAUTOGENERATETEXTCORE_NO_EXPORT TextAutoGenerateChat convertJsonToChat(const QString &json) const;
};
}
