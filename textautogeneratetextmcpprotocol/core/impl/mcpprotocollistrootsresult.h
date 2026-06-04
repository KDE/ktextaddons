/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRoot>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolListRootsResult
{
public:
    /*!
     */
    McpProtocolListRootsResult();
    /*!
     */
    ~McpProtocolListRootsResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolListRootsResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolListRootsResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolListRootsResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] QList<McpProtocolRoot> roots() const;
    /*!
     */
    void setRoots(const QList<McpProtocolRoot> &newRoots);

private:
    std::optional<McpProtocolMeta> mMeta;
    QList<McpProtocolRoot> mRoots;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolListRootsResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListRootsResult &t);
