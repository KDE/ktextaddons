/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importkmailautocorrection.h"
using namespace Qt::Literals::StringLiterals;

#include <QFile>
#include <QXmlStreamReader>
using namespace TextAutoCorrectionCore;

ImportKMailAutocorrection::ImportKMailAutocorrection() = default;

ImportKMailAutocorrection::~ImportKMailAutocorrection() = default;

bool ImportKMailAutocorrection::import(const QString &fileName, QString &errorMessage, LoadAttribute loadAttribute)
{
    Q_UNUSED(errorMessage);
    QFile xmlFile(fileName);
    if (!xmlFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    QXmlStreamReader xml(&xmlFile);
    mMaxFindStringLength = 0;
    mMinFindStringLength = 0;
    if (xml.readNextStartElement()) {
        while (xml.readNextStartElement()) {
            const QStringView xmlName = xml.name();
            if (xmlName == "UpperCaseExceptions"_L1) {
                if (loadAttribute == All) {
                    while (xml.readNextStartElement()) {
                        const QStringView tagname = xml.name();
                        if (tagname == "word"_L1) {
                            if (xml.attributes().hasAttribute(QStringLiteral("exception"))) {
                                const QString exception = xml.attributes().value(QStringLiteral("exception")).toString();
                                mUpperCaseExceptions += exception;
                                xml.skipCurrentElement();
                            }
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if (xmlName == "TwoUpperLetterExceptions"_L1) {
                if (loadAttribute == All) {
                    while (xml.readNextStartElement()) {
                        const QStringView tagname = xml.name();
                        if (tagname == "word"_L1) {
                            if (xml.attributes().hasAttribute(QStringLiteral("exception"))) {
                                const QString exception = xml.attributes().value(QStringLiteral("exception")).toString();
                                mTwoUpperLetterExceptions += exception;
                                xml.skipCurrentElement();
                            }
                        } else {
                            xml.skipCurrentElement();
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if (xmlName == "DoubleQuote"_L1) {
                if (loadAttribute == All) {
                    if (xml.readNextStartElement()) {
                        const QStringView tagname = xml.name();
                        if (tagname == "doublequote"_L1) {
                            mTypographicDoubleQuotes.begin = xml.attributes().value(QStringLiteral("begin")).toString().at(0);
                            mTypographicDoubleQuotes.end = xml.attributes().value(QStringLiteral("end")).toString().at(0);
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                        xml.skipCurrentElement();
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if (xmlName == "SimpleQuote"_L1) {
                if (loadAttribute == All) {
                    if (xml.readNextStartElement()) {
                        const QStringView tagname = xml.name();
                        if (tagname == "simplequote"_L1) {
                            const QString simpleQuoteBegin = xml.attributes().value(QStringLiteral("begin")).toString();
                            if (!simpleQuoteBegin.isEmpty()) { // crash when we have old data with bug.
                                mTypographicSingleQuotes.begin = simpleQuoteBegin.at(0);
                            }
                            const QString simpleQuoteEnd = xml.attributes().value(QStringLiteral("end")).toString();
                            if (!simpleQuoteEnd.isEmpty()) { // crash when we have old data with bug.
                                mTypographicSingleQuotes.end = simpleQuoteEnd.at(0);
                            }
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                        xml.skipCurrentElement();
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if (xmlName == "SuperScript"_L1) {
                if (loadAttribute == All || loadAttribute == SuperScript) {
                    while (xml.readNextStartElement()) {
                        const QStringView tagname = xml.name();
                        if (tagname == "item"_L1) {
                            const QString find = xml.attributes().value(QStringLiteral("find")).toString();
                            const QString super = xml.attributes().value(QStringLiteral("super")).toString();
                            mSuperScriptEntries.insert(find, super);
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if (xmlName == "items"_L1) {
                if (loadAttribute == All) {
                    while (xml.readNextStartElement()) {
                        const QStringView tagname = xml.name();
                        if (tagname == "item"_L1) {
                            const QString find = xml.attributes().value(QStringLiteral("find")).toString();
                            const QString replace = xml.attributes().value(QStringLiteral("replace")).toString();
                            const int findLenght(find.length());
                            mMaxFindStringLength = qMax(findLenght, mMaxFindStringLength);
                            mMinFindStringLength = qMin(findLenght, mMinFindStringLength);
                            mAutocorrectEntries.insert(find, replace);
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else {
                // TODO verify
                xml.skipCurrentElement();
            }
        }
    }
    return true;
}
