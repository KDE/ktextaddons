/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowserfindbartest.h"
using namespace Qt::Literals::StringLiterals;

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

    QTest::newRow("empty") << QString() << u"blabla"_s << TextCustomEditor::TextEditFindBarBase::FindFlags() << false;
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindRespectDiacritics;
        QTest::newRow("empty-1") << QString() << u"blabla"_s << flags << false;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindCaseSensitively;
        QTest::newRow("empty-2") << QString() << u"blabla"_s << flags << false;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("findwholewords-1") << u"bla bla"_s << u"bla"_s << flags << true;

        QTest::newRow("findwholewords-2") << u"blabla"_s << u"bla"_s << flags << false;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindRespectDiacritics;
        QTest::newRow("find-diacritics-1") << u"numéro numéro"_s << u"numero"_s << flags << false;

        QTest::newRow("find-diacritics-2") << u"numéro numéro"_s << u"numéro"_s << flags << true;
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
