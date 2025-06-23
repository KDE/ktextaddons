/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importkmailautocorrection.h"

#include <QFile>
#include <QXmlStreamReader>
using namespace Qt::Literals::StringLiterals;
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
                            if (xml.attributes().hasAttribute(u"exception"_s)) {
                                const QString exception = xml.attributes().value(u"exception"_s).toString();
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
                            if (xml.attributes().hasAttribute(u"exception"_s)) {
                                const QString exception = xml.attributes().value(u"exception"_s).toString();
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
                            mTypographicDoubleQuotes.begin = xml.attributes().value(u"begin"_s).toString().at(0);
                            mTypographicDoubleQuotes.end = xml.attributes().value(u"end"_s).toString().at(0);
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
                            const QString simpleQuoteBegin = xml.attributes().value(u"begin"_s).toString();
                            if (!simpleQuoteBegin.isEmpty()) { // crash when we have old data with bug.
                                mTypographicSingleQuotes.begin = simpleQuoteBegin.at(0);
                            }
                            const QString simpleQuoteEnd = xml.attributes().value(u"end"_s).toString();
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
                            const QString find = xml.attributes().value(u"find"_s).toString();
                            const QString super = xml.attributes().value(u"super"_s).toString();
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
                            const QString find = xml.attributes().value(u"find"_s).toString();
                            const QString replace = xml.attributes().value(u"replace"_s).toString();
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
