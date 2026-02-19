/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textgrammarcheck_export.h"
#include <QObject>
#include <QString>
#include <QStringList>
class QDebug;
namespace TextGrammarCheck
{
/*!
 * \class TextGrammarCheck::GrammarAction
 * \inheaderfile TextGrammarCheck/GrammarAction
 * \inmodule TextGrammarCheck
 * \brief Represents a grammar correction action.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammarAction
{
public:
    /*! Constructs a new GrammarAction. */
    GrammarAction();

    /*! Returns the replacement text for this action. */
    [[nodiscard]] QString replacement() const;
    /*! Sets the replacement text for this action. */
    void setReplacement(const QString &replacement);

    /*! Returns the starting position where this action applies. */
    [[nodiscard]] int start() const;
    /*! Sets the starting position where this action applies. */
    void setStart(int start);

    /*! Returns the length of text this action applies to. */
    [[nodiscard]] int length() const;
    /*! Sets the length of text this action applies to. */
    void setLength(int end);

    /*! Returns the list of suggestions for this action. */
    [[nodiscard]] QStringList suggestions() const;
    /*! Sets the list of suggestions for this action. */
    void setSuggestions(const QStringList &suggestions);

    /*! Returns the block ID this action is related to. */
    [[nodiscard]] int blockId() const;
    /*! Sets the block ID this action is related to. */
    void setBlockId(int blockId);

    /*! Returns the information URLs for this action. */
    [[nodiscard]] QStringList infoUrls() const;
    /*! Sets the information URLs for this action. */
    void setInfoUrls(const QStringList &urls);

private:
    QStringList mSuggestions;
    QStringList mInfoUrls;
    QString mReplacement;
    int mStart = -1;
    int mLength = -1;
    int mBlockId = -1;
};
}
Q_DECLARE_METATYPE(TextGrammarCheck::GrammarAction)
/*!
 */
TEXTGRAMMARCHECK_EXPORT QDebug operator<<(QDebug d, const TextGrammarCheck::GrammarAction &t);
