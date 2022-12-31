/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheckprivate_export.h"
#include <TextGrammarCheck/GrammarError>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_TESTS_EXPORT GrammalecteGrammarError : public GrammarError
{
public:
    GrammalecteGrammarError();
    ~GrammalecteGrammarError() override;
    void parse(const QJsonObject &obj, int blockindex) override;

private:
    Q_REQUIRED_RESULT static QStringList parseSuggestion(const QJsonObject &obj);
    Q_REQUIRED_RESULT static QColor parseColor(const QJsonObject &obj);
};
}
Q_DECLARE_METATYPE(TextGrammarCheck::GrammalecteGrammarError)
Q_DECLARE_TYPEINFO(TextGrammarCheck::GrammalecteGrammarError, Q_MOVABLE_TYPE);
