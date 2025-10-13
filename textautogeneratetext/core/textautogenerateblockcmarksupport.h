/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <TextUtils/TextUtilsBlockCMarkSupport>
namespace TextAutoGenerateText
{
class TextAutoGenerateBlockCMarkSupport : public TextUtils::TextUtilsBlockCMarkSupport
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
                                         int &numberOfTextSearched) override;
};

}
