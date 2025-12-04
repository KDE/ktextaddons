/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QColor>
class QDebug;
#include <QJsonObject>
#include <QString>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_EXPORT GrammarError
{
public:
    GrammarError();
    virtual ~GrammarError();
    [[nodiscard]] QColor color() const;
    void setColor(const QColor &color);

    [[nodiscard]] QString error() const;
    void setError(const QString &error);

    [[nodiscard]] int blockId() const;
    void setBlockId(int blockId);

    [[nodiscard]] int start() const;
    void setStart(int start);

    [[nodiscard]] int length() const;
    void setLength(int length);

    [[nodiscard]] QStringList suggestions() const;
    void setSuggestions(const QStringList &suggestions);

    [[nodiscard]] bool isValid() const;

    virtual void parse(const QJsonObject &obj, int blockindex);

    [[nodiscard]] bool operator==(const GrammarError &other) const;

    [[nodiscard]] QString option() const;
    void setOption(const QString &option);

    [[nodiscard]] QString rule() const;
    void setRule(const QString &rule);

    [[nodiscard]] QString url() const;
    void setUrl(const QString &url);

protected:
    QStringList mSuggestions;
    QString mError;
    QString mOption;
    QString mRule;
    QString mUrl;
    QColor mColor;
    int mBlockId = -1;
    int mStart = -1;
    int mLength = -1;
};
}
Q_DECLARE_METATYPE(TextGrammarCheck::GrammarError)
Q_DECLARE_TYPEINFO(TextGrammarCheck::GrammarError, Q_MOVABLE_TYPE);
TEXTGRAMMARCHECK_EXPORT QDebug operator<<(QDebug d, const TextGrammarCheck::GrammarError &t);
