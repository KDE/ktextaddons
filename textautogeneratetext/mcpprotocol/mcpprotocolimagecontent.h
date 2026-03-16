/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QByteArray>
#include <QString>
namespace McpProtocol
{
class McpProtocolImageContent
{
public:
    McpProtocolImageContent();
    ~McpProtocolImageContent();

    [[nodiscard]] static QByteArray type();

    [[nodiscard]] QString mimeType() const;
    void setMimeType(const QString &newMimeType);

private:
    QString mMimeType;
};
}
