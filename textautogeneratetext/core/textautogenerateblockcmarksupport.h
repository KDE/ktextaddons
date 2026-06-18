/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <TextUtils/TextUtilsBlockCMarkSupport>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateBlockCMarkSupport : public TextUtils::TextUtilsBlockCMarkSupport
{
public:
    TextAutoGenerateBlockCMarkSupport();
    ~TextAutoGenerateBlockCMarkSupport() override;

protected:
    [[nodiscard]] QString addHighlighter(const QString &str,
                                         const QString &language,
                                         const QString &searchText,
                                         const QByteArray &uuid,
                                         int &blockCodeIndex,
                                         int &numberOfTextSearched,
                                         int hightLightStringIndex) override;
};

}
