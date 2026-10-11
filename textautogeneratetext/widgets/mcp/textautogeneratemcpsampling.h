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
namespace TextAutoGenerateMcpSampling
{
/*!
 * Ask user to confirm sampling requests of MCP servers before sending them to LLM (dialog parent: \a parent).
 */
TEXTAUTOGENERATETEXT_TESTS_EXPORT void installSamplingHandler(TextAutoGenerateMcpToolsManager *toolsManager, QWidget *parent);
}
}
