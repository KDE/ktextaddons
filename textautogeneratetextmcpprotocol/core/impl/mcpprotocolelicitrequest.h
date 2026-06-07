/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
// #include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestParams>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolElicitRequest
{
public:
    /*!
     */
    McpProtocolElicitRequest();
    /*!
     */
    ~McpProtocolElicitRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolElicitRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolElicitRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

private:
    McpProtocolUtils::RequestId mId;
    // TODO
    // McpProtocolElicitRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &t);
