/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
class QWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateMcpToolsManager;
namespace TextAutoGenerateMcpElicitation
{
/*!
 * Ask user to answer elicitation requests of MCP servers (dialog parent: \a parent).
 */
TEXTAUTOGENERATETEXT_TESTS_EXPORT void installElicitationHandler(TextAutoGenerateMcpToolsManager *toolsManager, QWidget *parent);
}
}
