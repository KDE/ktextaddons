/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheckprivate_export.h"
#include <QObject>
namespace TextGrammarCheck
{
class LanguageToolComboBox;
class TEXTGRAMMARCHECK_TESTS_EXPORT LanguageToolUpdateComboBox : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolUpdateComboBox(QObject *parent = nullptr);
    ~LanguageToolUpdateComboBox() override;

    [[nodiscard]] LanguageToolComboBox *languageToolCombobox() const;
    void setLanguageToolCombobox(LanguageToolComboBox *languageToolCombobox);

    void checkListOfLanguagesFromSpecificPath(const QString &url);
    void firstRefreshListOfLanguages();
    void refreshListOfLanguages();

    [[nodiscard]] QWidget *parentWidget() const;
    void setParentWidget(QWidget *parentWidget);

private:
    void slotGetLanguagesFinished(const QString &result);
    void slotGetLanguagesError(const QString &error);
    static inline bool mBListWasLoaded = false;
    LanguageToolComboBox *mLanguageToolCombobox = nullptr;
    QWidget *mParentWidget = nullptr;
};
}
