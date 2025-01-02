/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheckprivate_export.h"

#include "common/grammarerror.h"
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_TESTS_EXPORT LanguageToolParser
{
public:
    LanguageToolParser();
    ~LanguageToolParser();
    [[nodiscard]] QVector<TextGrammarCheck::GrammarError> parseResult(const QJsonObject &obj) const;
};
}
