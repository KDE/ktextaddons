/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateattachments.h"
#include "textautogeneratetextcore_memory_debug.h"
using namespace TextAutoGenerateText;

TextAutoGenerateAttachments::TextAutoGenerateAttachments()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachments created " << this;
}

TextAutoGenerateAttachments::~TextAutoGenerateAttachments()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachments deleted " << this;
}

TextAutoGenerateAttachments::TextAutoGenerateAttachments(const TextAutoGenerateAttachments &other)
    : QSharedData(other)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachments created " << this;
}

bool TextAutoGenerateAttachments::isEmpty() const
{
    return mMessageAttachments.isEmpty();
}
