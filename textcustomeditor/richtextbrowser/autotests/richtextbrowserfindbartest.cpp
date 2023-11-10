/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowserfindbartest.h"
#include "richtextbrowser/richtextbrowserfindbar.h"
#include <QTest>
#include <QTextBrowser>

QTEST_MAIN(RichTextBrowserFindBarTest)
Q_DECLARE_METATYPE(TextCustomEditor::TextEditFindBarBase::FindFlags)
RichTextBrowserFindBarTest::RichTextBrowserFindBarTest(QObject *parent)
    : QObject{parent}
{
}

void RichTextBrowserFindBarTest::shouldHaveDefaultValues()
{
    QTextBrowser edit;
    TextCustomEditor::RichTextBrowserFindBar w(&edit);
    QVERIFY(w.text().isEmpty());
}

class RichTextEditFindBarExample : public TextCustomEditor::RichTextBrowserFindBar
{
public:
    explicit RichTextEditFindBarExample(QTextBrowser *view, QWidget *parent = nullptr)
        : RichTextBrowserFindBar(view, parent)
    {
    }
    ~RichTextEditFindBarExample() override = default;
    [[nodiscard]] bool searchInDocument(const QString &text, TextEditFindBarBase::FindFlags searchOptions) override
    {
        return TextCustomEditor::RichTextBrowserFindBar::searchInDocument(text, searchOptions);
    }

    [[nodiscard]] bool searchInDocument(const QRegularExpression &regExp, TextEditFindBarBase::FindFlags searchOptions) override
    {
        return TextCustomEditor::RichTextBrowserFindBar::searchInDocument(regExp, searchOptions);
    }
};

void RichTextBrowserFindBarTest::shouldSearchText_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<QString>("searchText");
    QTest::addColumn<TextCustomEditor::TextEditFindBarBase::FindFlags>("flags");
    QTest::addColumn<bool>("found");

    QTest::newRow("empty") << QString() << QStringLiteral("blabla") << TextCustomEditor::TextEditFindBarBase::FindFlags() << false;
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindRespectDiacritics;
        QTest::newRow("empty-1") << QString() << QStringLiteral("blabla") << flags << false;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindCaseSensitively;
        QTest::newRow("empty-2") << QString() << QStringLiteral("blabla") << flags << false;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("findwholewords-1") << QStringLiteral("bla bla") << QStringLiteral("bla") << flags << true;

        QTest::newRow("findwholewords-2") << QStringLiteral("blabla") << QStringLiteral("bla") << flags << false;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindRespectDiacritics;
        QTest::newRow("find-diacritics-1") << QStringLiteral("numéro numéro") << QStringLiteral("numero") << flags << false;

        QTest::newRow("find-diacritics-2") << QStringLiteral("numéro numéro") << QStringLiteral("numéro") << flags << true;
    }
}

void RichTextBrowserFindBarTest::shouldSearchText()
{
    QFETCH(QString, text);
    QFETCH(QString, searchText);
    QFETCH(TextCustomEditor::TextEditFindBarBase::FindFlags, flags);
    QFETCH(bool, found);

    QTextBrowser edit;
    RichTextEditFindBarExample w(&edit);
    edit.setPlainText(text);

    QCOMPARE(w.searchInDocument(searchText, flags), found);
}

#include "moc_richtextbrowserfindbartest.cpp"
