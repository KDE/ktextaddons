/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresultutiltest.h"
using namespace Qt::Literals::StringLiterals;

#include "common/grammarresultutil.h"
#include <QTest>
#include <QTextDocument>
QTEST_MAIN(GrammarResultUtilTest)
GrammarResultUtilTest::GrammarResultUtilTest(QObject *parent)
    : QObject{parent}
{
}

void GrammarResultUtilTest::shouldReplaceWord()
{
    typedef QVector<TextGrammarCheck::GrammarAction> ListGrammarActions;
    typedef QVector<TextGrammarCheck::GrammarError> ErrorInfosList;
    QFETCH(QString, initialText);
    QFETCH(QStringList, replacementWord);
    QFETCH(ErrorInfosList, grammarErrors);
    QFETCH(ListGrammarActions, listGrammarActions);
    QFETCH(QString, resultText);

    QTextDocument doc;
    doc.setPlainText(initialText);
    TextGrammarCheck::GrammarResultUtil::applyGrammarResult(grammarErrors, &doc, Qt::red);
    int i = 0;
    for (const auto &action : listGrammarActions) {
        TextGrammarCheck::GrammarResultUtil::replaceWord(action, replacementWord.at(i), &doc);
        ++i;
    }
    QCOMPARE(doc.toPlainText(), resultText);
}

void GrammarResultUtilTest::shouldReplaceWord_data()
{
    QTest::addColumn<QString>("initialText");
    QTest::addColumn<QStringList>("replacementWord");
    QTest::addColumn<QVector<TextGrammarCheck::GrammarError>>("grammarErrors");
    QTest::addColumn<QVector<TextGrammarCheck::GrammarAction>>("listGrammarActions");
    QTest::addColumn<QString>("resultText");
    {
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        QTest::newRow("noerror") << QString() << QStringList() << grammarErrorLists << lstGrammarActions << QString();
    }
    {
        const QString text = u"Boo foo, ah car"_s;
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        QTest::newRow("noerror2") << text << QStringList() << grammarErrorLists << lstGrammarActions << text;
    }
    {
        const QString text = u"Boo foo, ah car"_s;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {u"joo"_s};
        const QString result = u"joo foo, ah car"_s;
        QTest::newRow("error1") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
    {
        const QString text = u"Boo foo, ah car"_s;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = QStringList{u"ppppppp"_s};
        const QString result = u"ppppppp foo, ah car"_s;
        QTest::newRow("error2-word-big") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
    {
        const QString text = u"Boo foo, ah car"_s;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = QStringList{u"p"_s};
        const QString result = u"p foo, ah car"_s;
        QTest::newRow("error3-word-smaller") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }

    // Two errors
    {
        const QString text = u"Boo foo, ah car"_s;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(4);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(4);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {u"joo"_s, QStringLiteral("AAA")};
        const QString result = u"joo AAA, ah car"_s;
        QTest::newRow("error1-with-two-errors") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
    // Bug 459113
    {
        const QString text = u"Boo foo, ah car"_s;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(4);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(6);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {u"jooAA"_s, QStringLiteral("AAA")};
        const QString result = u"jooAA AAA, ah car"_s;
        QTest::newRow("error1-with-two-errors-bigger") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
    {
        const QString text = u"Boo\n foo, ah car"_s;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(5);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(2);
            act.setStart(1);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {u"jooAA"_s, QStringLiteral("AAA")};
        const QString result = u"jooAA\n AAA, ah car"_s;
        QTest::newRow("error1-with-two-errors-bigger-1") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }

    {
        const QString text = u"Boo\n foo, ah car"_s;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(5);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(2);
            act.setStart(1);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {u"b"_s, QStringLiteral("AAA")};
        const QString result = u"b\n AAA, ah car"_s;
        QTest::newRow("error1-with-two-errors-smaller-1") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }

    {
        const QString text = u"Je suis  la qui empeche\nil est la.\n tout passage dans l'herbe"_s;
        QVector<TextGrammarCheck::GrammarError> grammarErrorLists;
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(7);
            err.setLength(2);
            grammarErrorLists.append(err);
        }
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(1);
            err.setStart(14);
            err.setLength(7);
            grammarErrorLists.append(err);
        }
        {
            TextGrammarCheck::GrammarError err;
            err.setBlockId(2);
            err.setStart(3);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<TextGrammarCheck::GrammarAction> lstGrammarActions;
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(7);
            act.setLength(2);
            lstGrammarActions.append(act);
        }
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(1);
            act.setStart(15);
            act.setLength(7);
            lstGrammarActions.append(act);
        }
        {
            TextGrammarCheck::GrammarAction act;
            act.setBlockId(2);
            act.setStart(3);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {u" "_s, QStringLiteral("EMPECHE"), QStringLiteral("A")};
        const QString result = u"Je suis la qui EMPECHE\nil A la.\n tout passage dans l'herbe"_s;
        QTest::newRow("error3") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
}

#include "moc_grammarresultutiltest.cpp"
