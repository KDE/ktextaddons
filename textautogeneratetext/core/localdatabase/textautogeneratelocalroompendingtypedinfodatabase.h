/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "core/textautogeneratechatsettings.h"
#include "textautogeneratelocaldatabaseabstract.h"
#include "textautogeneratetext_private_export.h"
#include <QMap>
class QSqlTableModel;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateLocalRoomPendingTypedInfoDatabase : public TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalRoomPendingTypedInfoDatabase();
    ~TextAutoGenerateLocalRoomPendingTypedInfoDatabase() override;

    [[nodiscard]] std::unique_ptr<QSqlTableModel> createRoomsModel(const QString &accountName) const;

    void
    updateRoomPendingTypedInfo(const QString &accountName, const QByteArray &roomId, const TextAutoGenerateChatSettings::PendingTypedInfo &pendingTypedInfo);
    void deleteRoomPendingTypedInfo(const QString &accountName, const QByteArray &roomId);

    [[nodiscard]] QMap<QByteArray /*RoomId*/, TextAutoGenerateChatSettings::PendingTypedInfo> loadRoomPendingTypedInfo(const QString &accountName);

protected:
    [[nodiscard]] QString schemaDataBase() const override;

private:
    [[nodiscard]] TextAutoGenerateChatSettings::PendingTypedInfo convertJsonToRoomPendingTypedInfo(const QString &json);
};
}
