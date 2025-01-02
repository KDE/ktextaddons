/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "languageinfo.h"
#include "textgrammarcheckprivate_export.h"
#include <QVector>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_TESTS_EXPORT LanguageToolListOfLanguagesParser
{
public:
    LanguageToolListOfLanguagesParser();
    ~LanguageToolListOfLanguagesParser();
    [[nodiscard]] QVector<LanguageInfo> parseResult(const QJsonArray &obj) const;
};
}
