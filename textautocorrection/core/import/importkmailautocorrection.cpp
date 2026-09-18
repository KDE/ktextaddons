/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importkmailautocorrection.h"

#include <QFile>
#include <QXmlStreamReader>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoCorrectionCore;

ImportKMailAutocorrection::ImportKMailAutocorrection() = default;

ImportKMailAutocorrection::~ImportKMailAutocorrection() = default;

bool ImportKMailAutocorrection::import(const QString &fileName, [[maybe_unused]] QString &errorMessage, LoadAttribute loadAttribute)
{
    QFile xmlFile(fileName);
    if (!xmlFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    QXmlStreamReader xml(&xmlFile);
    mMaxFindStringLength = 0;
    mMinFindStringLength = 0;
    if (xml.readNextStartElement()) {
        while (xml.readNextStartElement()) {
            if (const QStringView xmlName = xml.name(); xmlName == "UpperCaseExceptions"_L1) {
                if (loadAttribute == All) {
                    while (xml.readNextStartElement()) {
                        if (const QStringView tagname = xml.name(); tagname == "word"_L1) {
                            if (xml.attributes().hasAttribute("exception"_L1)) {
                                const QString exception = xml.attributes().value("exception"_L1).toString();
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
                        if (const QStringView tagname = xml.name(); tagname == "word"_L1) {
                            if (xml.attributes().hasAttribute("exception"_L1)) {
                                const QString exception = xml.attributes().value("exception"_L1).toString();
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
                        if (const QStringView tagname = xml.name(); tagname == "doublequote"_L1) {
                            if (const auto temp = xml.attributes().value("begin"_L1).toString(); !temp.isEmpty()) {
                                mTypographicDoubleQuotes.begin = temp.at(0);
                            }
                            if (const auto temp = xml.attributes().value("end"_L1).toString(); !temp.isEmpty()) {
                                mTypographicDoubleQuotes.end = temp.at(0);
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
            } else if (xmlName == "SimpleQuote"_L1) {
                if (loadAttribute == All) {
                    if (xml.readNextStartElement()) {
                        if (const QStringView tagname = xml.name(); tagname == "simplequote"_L1) {
                            const QString simpleQuoteBegin = xml.attributes().value("begin"_L1).toString();
                            if (!simpleQuoteBegin.isEmpty()) { // crash when we have old data with bug.
                                mTypographicSingleQuotes.begin = simpleQuoteBegin.at(0);
                            }
                            const QString simpleQuoteEnd = xml.attributes().value("end"_L1).toString();
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
                        if (const QStringView tagname = xml.name(); tagname == "item"_L1) {
                            const QString find = xml.attributes().value("find"_L1).toString();
                            const QString super = xml.attributes().value("super"_L1).toString();
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
                        if (const QStringView tagname = xml.name(); tagname == "item"_L1) {
                            const QString find = xml.attributes().value("find"_L1).toString();
                            const QString replace = xml.attributes().value("replace"_L1).toString();
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
