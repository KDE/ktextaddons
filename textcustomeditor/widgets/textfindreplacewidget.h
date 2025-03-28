/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_private_export.h"
#include "texteditfindbarbase.h"
#include <QWidget>

class QAction;
class QLineEdit;
class QPushButton;
namespace TextCustomEditor
{
class TEXTCUSTOMEDITOR_TESTS_EXPORT TextFindWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextFindWidget(QWidget *parent = nullptr);
    ~TextFindWidget() override;

    [[nodiscard]] TextEditFindBarBase::FindFlags searchOptions() const;

    QLineEdit *searchLineEdit() const;

    void setFoundMatch(bool match);

    [[nodiscard]] bool isRegularExpression() const;
    [[nodiscard]] QRegularExpression searchRegularExpression() const;

    [[nodiscard]] QString searchText() const;

Q_SIGNALS:
    void findNext();
    void findPrev();
    void clearSearch();
    void autoSearch(const QString &);
    void updateSearchOptions();
    void searchStringEmpty(bool);

private:
    void slotAutoSearch(const QString &str);
    void slotRegularExpressionChanged(bool b);
    QLineEdit *const mSearch;
    QAction *mCaseSensitiveAct = nullptr;
    QAction *mWholeWordAct = nullptr;
    QAction *mRegularExpressionAct = nullptr;
    QAction *mRespectDiacriticAct = nullptr;

    QPushButton *const mFindPrevBtn;
    QPushButton *const mFindNextBtn;
};

class TEXTCUSTOMEDITOR_TESTS_EXPORT TextReplaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextReplaceWidget(QWidget *parent = nullptr);
    ~TextReplaceWidget() override;

    QLineEdit *replaceLineEdit() const;

public Q_SLOTS:
    void slotSearchStringEmpty(bool);

Q_SIGNALS:
    void replaceText();
    void replaceAllText();

private:
    QLineEdit *const mReplace;
    QPushButton *const mReplaceBtn;
    QPushButton *const mReplaceAllBtn;
};
}
