/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "core/textautogeneratechatsettings.h"
#include "textautogeneratelocaldatabaseabstract.h"
#include <QMap>
class QSqlTableModel;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateLocalChatPendingTypedInfoDatabase : public TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalChatPendingTypedInfoDatabase();
    ~TextAutoGenerateLocalChatPendingTypedInfoDatabase() override;

    [[nodiscard]] std::unique_ptr<QSqlTableModel> createChatPendingInfoModel() const;

    void updateChatPendingTypedInfo(const QByteArray &roomId, const TextAutoGenerateChatSettings::PendingTypedInfo &pendingTypedInfo);
    void deleteChatPendingTypedInfo(const QByteArray &roomId);

    [[nodiscard]] QMap<QByteArray /*RoomId*/, TextAutoGenerateChatSettings::PendingTypedInfo> loadChatPendingTypedInfo();

protected:
    [[nodiscard]] QString schemaDataBase() const override;

private:
    [[nodiscard]] TextAutoGenerateChatSettings::PendingTypedInfo convertJsonToChatPendingTypedInfo(const QString &json);
};
}
