/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "plaintexteditfindbartest.h"
using namespace Qt::Literals::StringLiterals;

#include "plaintexteditor/plaintexteditfindbar.h"
#include "widgets/findutils.h"
#include <QPlainTextEdit>
#include <QTest>

QTEST_MAIN(PlainTextEditFindBarTest)
Q_DECLARE_METATYPE(TextCustomEditor::TextEditFindBarBase::FindFlags)
PlainTextEditFindBarTest::PlainTextEditFindBarTest(QObject *parent)
    : QObject{parent}
{
}

void PlainTextEditFindBarTest::shouldHaveDefaultValues()
{
    QPlainTextEdit edit;
    TextCustomEditor::PlainTextEditFindBar w(&edit);
    QVERIFY(w.text().isEmpty());
}

class PlainTextEditFindBarExample : public TextCustomEditor::PlainTextEditFindBar
{
public:
    explicit PlainTextEditFindBarExample(QPlainTextEdit *view, QWidget *parent = nullptr)
        : PlainTextEditFindBar(view, parent)
    {
    }
    ~PlainTextEditFindBarExample() override = default;
    [[nodiscard]] bool searchInDocument(const QString &text, TextEditFindBarBase::FindFlags searchOptions) override
    {
        return TextCustomEditor::PlainTextEditFindBar::searchInDocument(text, searchOptions);
    }

    [[nodiscard]] bool searchInDocument(const QRegularExpression &regExp, TextEditFindBarBase::FindFlags searchOptions) override
    {
        return TextCustomEditor::PlainTextEditFindBar::searchInDocument(regExp, searchOptions);
    }
};

void PlainTextEditFindBarTest::shouldSearchText_data()
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
        QTest::newRow("find-diacritics-3") << u"numéro numéro il est là. Numero numéro"_s << u"numero"_s << flags << true;
    }
}

void PlainTextEditFindBarTest::shouldSearchText()
{
    QFETCH(QString, text);
    QFETCH(QString, searchText);
    QFETCH(TextCustomEditor::TextEditFindBarBase::FindFlags, flags);
    QFETCH(bool, found);

    QPlainTextEdit edit;
    PlainTextEditFindBarExample w(&edit);
    edit.setPlainText(text);

    QCOMPARE(w.searchInDocument(searchText, flags), found);
}

void PlainTextEditFindBarTest::shouldReplaceAllText_data()
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
        QTest::newRow("wholewords-no-diacritics-3") << u"voiture voiture voiture"_s << u"réunion"_s << QStringLiteral("replace") << flags << 0
                                                    << u"voiture voiture voiture"_s;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics-3") << u"voiture voiture il est là. voiture"_s << u"voiture"_s << u"replace"_s << flags << 3
                                                    << u"replace replace il est là. replace"_s;
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics-4") << u"réunion réunion . Test… réunion"_s << u"réunion"_s << u"replace"_s << flags << 3
                                                    << u"replace replace . Test… replace"_s;
    }
}

void PlainTextEditFindBarTest::shouldReplaceAllText()
{
    QFETCH(QString, text);
    QFETCH(QString, searchText);
    QFETCH(QString, replaceText);
    QFETCH(TextCustomEditor::TextEditFindBarBase::FindFlags, flags);
    QFETCH(int, nbElement);
    QFETCH(QString, resultStr);

    QPlainTextEdit edit;
    edit.setPlainText(text);
    PlainTextEditFindBarExample w(&edit);
    const int nbElementResult = TextCustomEditor::FindUtils::replaceAll(&edit, searchText, replaceText, flags);
    QCOMPARE(edit.toPlainText(), resultStr);
    QCOMPARE(nbElementResult, nbElement);
}

#include "moc_plaintexteditfindbartest.cpp"
