/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>

#include "textautogeneratetext_private_export.h"
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchJob : public QObject
{
    Q_OBJECT
public:
    /*! Constructs a new TextAutoGenerateSearchJob associated with the given @p manager and @p parent. */
    explicit TextAutoGenerateSearchJob(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    /*! Destroys the TextAutoGenerateSearchJob object. */
    ~TextAutoGenerateSearchJob() override;

    /*! Returns whether the search job can be started. */
    [[nodiscard]] bool canStart() const;

    /*! Starts the search job. */
    void start();
    /*! Returns the search text. */
    [[nodiscard]] QString searchText() const;
    /*! Sets the search text to @p newSearchText. */
    void setSearchText(const QString &newSearchText);

Q_SIGNALS:
    /*! Emitted when search is done with the list of found messages in @p msgs. */
    void searchDone(const QList<TextAutoGenerateText::TextAutoGenerateSearchMessage> &msgs);

private:
    QString mSearchText;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
