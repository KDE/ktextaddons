/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "plaintexteditfindbartest.h"
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
        QTest::newRow("find-diacritics-3") << QStringLiteral("numéro numéro il est là. Numero numéro") << QStringLiteral("numero") << flags << true;
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

    QTest::newRow("empty") << QString() << QStringLiteral("blabla") << QStringLiteral("replace") << TextCustomEditor::TextEditFindBarBase::FindFlags() << 0
                           << QString();

    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords") << QStringLiteral("bla bla") << QStringLiteral("bla") << QStringLiteral("replace") << flags << 2
                                    << QStringLiteral("replace replace");
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        flags |= TextCustomEditor::TextEditFindBarBase::FindRespectDiacritics;
        QTest::newRow("wholewords-diacritics") << QStringLiteral("réunion reunion réunion") << QStringLiteral("réunion") << QStringLiteral("replace") << flags
                                               << 2 << QStringLiteral("replace reunion replace");
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics") << QStringLiteral("réunion reunion réunion") << QStringLiteral("réunion") << QStringLiteral("replace")
                                                  << flags << 3 << QStringLiteral("replace replace replace");
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics-2") << QStringLiteral("réunion réunion réunion") << QStringLiteral("réunion") << QStringLiteral("replace")
                                                    << flags << 3 << QStringLiteral("replace replace replace");
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics-3") << QStringLiteral("voiture voiture voiture") << QStringLiteral("réunion") << QStringLiteral("replace")
                                                    << flags << 0 << QStringLiteral("voiture voiture voiture");
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics-3") << QStringLiteral("voiture voiture il est là. voiture") << QStringLiteral("voiture")
                                                    << QStringLiteral("replace") << flags << 3 << QStringLiteral("replace replace il est là. replace");
    }
    {
        TextCustomEditor::TextEditFindBarBase::FindFlags flags;
        flags |= TextCustomEditor::TextEditFindBarBase::FindWholeWords;
        QTest::newRow("wholewords-no-diacritics-4") << QStringLiteral("réunion réunion . Test… réunion") << QStringLiteral("réunion")
                                                    << QStringLiteral("replace") << flags << 3 << QStringLiteral("replace replace . Test… replace");
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
