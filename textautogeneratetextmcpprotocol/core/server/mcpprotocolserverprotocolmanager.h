/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager
 * \brief The McpProtocolServerProtocolManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerProtocolManager
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerProtocolManager : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolServerProtocolManager(QObject *parent = nullptr);
    ~McpProtocolServerProtocolManager() override;
};

}
