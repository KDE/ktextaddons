/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtexteditfindbartest.h"
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
        QTest::newRow("wholewords-no-diacritics-2") << QStringLiteral("voiture voiture voiture") << QStringLiteral("réunion") << QStringLiteral("replace")
                                                    << flags << 0 << QStringLiteral("voiture voiture voiture");
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
