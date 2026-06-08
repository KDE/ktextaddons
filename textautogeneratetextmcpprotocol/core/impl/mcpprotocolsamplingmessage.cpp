/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsamplingmessage.h"
#include <QDebug>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSamplingMessage::McpProtocolSamplingMessage() = default;
McpProtocolSamplingMessage::~McpProtocolSamplingMessage() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSamplingMessage &t)
{
    // TODO
    return d;
}
