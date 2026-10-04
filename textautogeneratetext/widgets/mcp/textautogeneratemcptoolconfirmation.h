/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QString>
class QWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateMcpToolsManager;
namespace TextAutoGenerateMcpToolConfirmation
{
/*!
 * Ask user before running a tool of a MCP server (dialog parent: \a parent).
 */
TEXTAUTOGENERATETEXT_TESTS_EXPORT void installConfirmationHandler(TextAutoGenerateMcpToolsManager *toolsManager, QWidget *parent);
}
}
