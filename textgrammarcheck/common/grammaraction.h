/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

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

    Q_REQUIRED_RESULT QString replacement() const;
    void setReplacement(const QString &replacement);

    Q_REQUIRED_RESULT int start() const;
    void setStart(int start);

    Q_REQUIRED_RESULT int length() const;
    void setLength(int length);

    Q_REQUIRED_RESULT QStringList suggestions() const;
    void setSuggestions(const QStringList &suggestions);

    Q_REQUIRED_RESULT int blockId() const;
    void setBlockId(int blockId);

    Q_REQUIRED_RESULT QStringList infoUrls() const;
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
