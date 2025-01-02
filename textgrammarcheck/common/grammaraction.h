/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textgrammarcheck_export.h"
#include <QDebug>
#include <QString>
#include <QStringList>

namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_EXPORT GrammarAction
{
public:
    GrammarAction();

    [[nodiscard]] QString replacement() const;
    void setReplacement(const QString &replacement);

    [[nodiscard]] int start() const;
    void setStart(int start);

    [[nodiscard]] int length() const;
    void setLength(int length);

    [[nodiscard]] QStringList suggestions() const;
    void setSuggestions(const QStringList &suggestions);

    [[nodiscard]] int blockId() const;
    void setBlockId(int blockId);

    [[nodiscard]] QStringList infoUrls() const;
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
TEXTGRAMMARCHECK_EXPORT QDebug operator<<(QDebug d, const TextGrammarCheck::GrammarAction &t);
