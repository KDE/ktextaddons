/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QColor>
#include <QMetaType>
#include <QString>
class QDebug;
class QJsonObject;
namespace TextGrammarCheck
{
/*!
 * \class TextGrammarCheck::GrammarError
 * \inheaderfile TextGrammarCheck/GrammarError
 * \inmodule TextGrammarCheck
 * \brief Represents a grammar error found during checking.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammarError
{
public:
    /*! Constructs a new GrammarError. */
    GrammarError();
    /*! Destroys the error object. */
    virtual ~GrammarError();
    /*! Returns the color associated with this error. */
    [[nodiscard]] QColor color() const;
    /*! Sets the color associated with this error. */
    void setColor(const QColor &color);

    /*! Returns the error description. */
    [[nodiscard]] QString error() const;
    /*! Sets the error description. */
    void setError(const QString &error);

    /*! Returns the block ID where the error occurred. */
    [[nodiscard]] int blockId() const;
    /*! Sets the block ID where the error occurred. */
    void setBlockId(int blockId);

    /*! Returns the starting position of the error in the text. */
    [[nodiscard]] int start() const;
    /*! Sets the starting position of the error in the text. */
    void setStart(int start);

    /*! Returns the length of the error in the text. */
    [[nodiscard]] int length() const;
    /*! Sets the length of the error in the text. */
    void setLength(int length);

    /*! Returns the list of suggestions to fix the error. */
    [[nodiscard]] QStringList suggestions() const;
    /*! Sets the list of suggestions to fix the error. */
    void setSuggestions(const QStringList &suggestions);

    /*! Returns whether the error is valid. */
    [[nodiscard]] bool isValid() const;

    /*! Parses error information from a JSON object. */
    virtual void parse(const QJsonObject &obj, int blockindex);

    /*! Compares two errors for equality. */
    [[nodiscard]] bool operator==(const GrammarError &other) const;

    /*! Returns the option this error is related to. */
    [[nodiscard]] QString option() const;
    /*! Sets the option this error is related to. */
    void setOption(const QString &option);

    /*! Returns the rule that was violated. */
    [[nodiscard]] QString rule() const;
    /*! Sets the rule that was violated. */
    void setRule(const QString &rule);

    /*! Returns the URL for more information about this error. */
    [[nodiscard]] QString url() const;
    /*! Sets the URL for more information about this error. */
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
