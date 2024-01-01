/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheckprivate_export.h"
#include <QJsonObject>
#include <QVector>
#include <TextGrammarCheck/GrammarError>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_TESTS_EXPORT GrammalecteParser
{
public:
    GrammalecteParser();
    ~GrammalecteParser();
    [[nodiscard]] QVector<GrammarError> parseResult(const QJsonObject &obj) const;
};
}
