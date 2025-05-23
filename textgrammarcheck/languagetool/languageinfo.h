/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textgrammarcheckprivate_export.h"

#include <QObject>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_TESTS_EXPORT LanguageInfo
{
public:
    LanguageInfo();
    ~LanguageInfo();

    [[nodiscard]] QString name() const;
    void setName(const QString &name);

    [[nodiscard]] QString longCode() const;
    void setLongCode(const QString &longCode);

    [[nodiscard]] QString code() const;
    void setCode(const QString &code);

    [[nodiscard]] bool isValid() const;

    void parse(const QJsonObject &obj);

    [[nodiscard]] bool operator==(const LanguageInfo &other) const;

private:
    QString mName;
    QString mLongCode;
    QString mCode;
};
}
Q_DECLARE_METATYPE(TextGrammarCheck::LanguageInfo)
Q_DECLARE_TYPEINFO(TextGrammarCheck::LanguageInfo, Q_MOVABLE_TYPE);
