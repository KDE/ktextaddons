/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/grammarerror.h"
#include "textgrammarcheckprivate_export.h"
#include <QStringList>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_TESTS_EXPORT LanguageToolGrammarError : public GrammarError
{
public:
    LanguageToolGrammarError();
    ~LanguageToolGrammarError() override;
    void parse(const QJsonObject &obj, int blockindex) override;
    void setTesting(bool b);

private:
    [[nodiscard]] static QStringList parseSuggestion(const QJsonObject &obj);
    bool mTesting = false;
};
}
Q_DECLARE_METATYPE(TextGrammarCheck::LanguageToolGrammarError)
Q_DECLARE_TYPEINFO(TextGrammarCheck::LanguageToolGrammarError, Q_MOVABLE_TYPE);
