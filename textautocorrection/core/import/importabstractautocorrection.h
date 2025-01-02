/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QHash>
#include <QSet>
#include <QString>

#include "autocorrectionutils.h"

#include "textautocorrectioncore_export.h"
namespace TextAutoCorrectionCore
{
class TEXTAUTOCORRECTIONCORE_EXPORT ImportAbstractAutocorrection
{
    Q_GADGET
public:
    enum LoadAttribute {
        All = 0,
        SuperScript,
    };
    Q_ENUM(LoadAttribute)

    ImportAbstractAutocorrection();
    virtual ~ImportAbstractAutocorrection();

    virtual bool import(const QString &fileName, QString &errorMessage, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) = 0;

    [[nodiscard]] QSet<QString> upperCaseExceptions() const;
    [[nodiscard]] QSet<QString> twoUpperLetterExceptions() const;
    [[nodiscard]] QHash<QString, QString> autocorrectEntries() const;
    [[nodiscard]] QHash<QString, QString> superScriptEntries() const;

    [[nodiscard]] AutoCorrectionUtils::TypographicQuotes typographicSingleQuotes() const;
    [[nodiscard]] AutoCorrectionUtils::TypographicQuotes typographicDoubleQuotes() const;

    [[nodiscard]] int maxFindStringLenght() const;

    [[nodiscard]] int minFindStringLenght() const;

protected:
    int mMaxFindStringLength = 0;
    int mMinFindStringLength = 0;
    QSet<QString> mUpperCaseExceptions;
    QSet<QString> mTwoUpperLetterExceptions;
    QHash<QString, QString> mAutocorrectEntries;
    QHash<QString, QString> mSuperScriptEntries;
    AutoCorrectionUtils::TypographicQuotes mTypographicSingleQuotes;
    AutoCorrectionUtils::TypographicQuotes mTypographicDoubleQuotes;
};
}
