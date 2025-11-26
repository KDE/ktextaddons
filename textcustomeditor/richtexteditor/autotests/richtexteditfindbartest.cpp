/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtexteditfindbartest.h"
using namespace Qt::Literals::StringLiterals;

#include "richtexteditor/richtexteditfindbar.h"
#include "widgets/findutils.h"
#include <QTest>
#include <QTextEdit>

QTEST_MAIN(RichTextEditFindBarTest)
Q_DECLARE_METATYPE(TextCustomEditor::TextEditFindBarBase::FindFlags)
RichTextEditFindBarTest::RichTextEditFindBarTest(QObject *parent)
    : QObject{parent}
{
}

void RichTextEditFindBarTest::shouldHaveDefaultValues()
{
    QTextEdit edit;
    TextCustomEditor::RichTextEditFindBar w(&edit);
    QVERIFY(w.text().isEmpty());
}

class RichTextEditFindBarExample : public TextCustomEditor::RichTextEditFindBar
{
    Q_OBJECT
public:
    explicit RichTextEditFindBarExample(QTextEdit *view, QWidget *parent = nullptr)
        : RichTextEditFindBar(view, parent)
    {
    }
    ~RichTextEditFindBarExample() override = default;
    [[nodiscard]] bool searchInDocument(const QString &text, TextEditFindBarBase::FindFlags searchOptions) override
    {
        return TextCustomEditor::RichTextEditFindBar::searchInDocument(text, searchOptions);
    }

    [[nodiscard]] bool searchInDocument(const QRegularExpression &regExp, TextEditFindBarBase::FindFlags searchOptions) override
    {
        return TextCustomEditor::RichTextEditFindBar::searchInDocument(regExp, searchOptions);
    }
};

void RichTextEditFindBarTest::shouldSearchText_data()
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

void RichTextEditFindBarTest::shouldSearchText()
{
    QFETCH(QString, text);
    QFETCH(QString, searchText);
    QFETCH(TextCustomEditor::TextEditFindBarBase::FindFlags, flags);
    QFETCH(bool, found);

    QTextEdit edit;
    RichTextEditFindBarExample w(&edit);
    edit.setPlainText(text);

    QCOMPARE(w.searchInDocument(searchText, flags), found);
}

void RichTextEditFindBarTest::shouldReplaceAllText_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<QString>("searchText");
    QTest::addColumn<QString>("replaceText");
    QTest::addColumn<TextCustomEditor::TextEditFindBarBase::FindFlags>("flags");
    QTest::addColumn<int>("nbElement");
    QTest::addColumn<QString>("resultStr");

    QTest::newRow("empty") << QString() << u"blabla"_s << u"replace"_s << TextCustomEditor::TextEditFindBarBase::FindFlags() << 0 << QString();

    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords") << u"bla bla"_s << u"bla"_s << QStringLiteral("replace") << flags << 2 << u"replace replace"_s;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        flags |= TextCustomEditor::TextEditFindBarBase::FindRespectDiacritics;
        QTest::newRow("wholewords-diacritics") << u"réunion reunion réunion"_s << u"réunion"_s << QStringLiteral("replace") << flags << 2
                                               << u"replace reunion replace"_s;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics") << u"réunion reunion réunion"_s << u"réunion"_s << QStringLiteral("replace") << flags << 3
                                                  << u"replace replace replace"_s;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics-2") << u"réunion réunion réunion"_s << u"réunion"_s << QStringLiteral("replace") << flags << 3
                                                    << u"replace replace replace"_s;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics-2") << u"voiture voiture voiture"_s << u"réunion"_s << QStringLiteral("replace") << flags << 0
                                                    << u"voiture voiture voiture"_s;
    }
}

void RichTextEditFindBarTest::shouldReplaceAllText()
{
    QFETCH(QString, text);
    QFETCH(QString, searchText);
    QFETCH(QString, replaceText);
    QFETCH(TextCustomEditor::TextEditFindBarBase::FindFlags, flags);
    QFETCH(int, nbElement);
    QFETCH(QString, resultStr);

    QTextEdit edit;
    edit.setPlainText(text);
    RichTextEditFindBarExample w(&edit);
    const int nbElementResult = TextCustomEditor::FindUtils::replaceAll(&edit, searchText, replaceText, flags);
    QCOMPARE(edit.toPlainText(), resultStr);
    QCOMPARE(nbElementResult, nbElement);
}

#include "moc_richtexteditfindbartest.cpp"
#include "richtexteditfindbartest.moc"
