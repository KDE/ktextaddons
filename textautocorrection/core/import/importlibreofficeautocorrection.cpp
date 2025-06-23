/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importlibreofficeautocorrection.h"

#include "textautocorrection_debug.h"
#include <KLocalizedString>
#include <KZip>
#include <QDomDocument>
#include <QFile>
#include <QTemporaryDir>

using namespace TextAutoCorrectionCore;
using namespace Qt::Literals::StringLiterals;

ImportLibreOfficeAutocorrection::ImportLibreOfficeAutocorrection() = default;

ImportLibreOfficeAutocorrection::~ImportLibreOfficeAutocorrection()
{
    closeArchive();
}

void ImportLibreOfficeAutocorrection::closeArchive()
{
    if (mArchive) {
        if (mArchive->isOpen()) {
            mArchive->close();
        }
        delete mArchive;
        mArchive = nullptr;
    }

    delete mTempDir;
    mTempDir = nullptr;
}

bool ImportLibreOfficeAutocorrection::import(const QString &fileName, QString &errorMessage, LoadAttribute loadAttribute)
{
    // We Don't have it in LibreOffice
    if (loadAttribute == SuperScript) {
        return false;
    }
    closeArchive();
    mArchive = new KZip(fileName);
    const bool result = mArchive->open(QIODevice::ReadOnly);
    if (result) {
        importAutoCorrectionFile();
        return true;
    } else {
        qCWarning(TEXTAUTOCORRECTION_LOG) << "Impossible to open archive file";
        errorMessage = i18n("Archive cannot be opened in read mode.");
        return false;
    }
}

void ImportLibreOfficeAutocorrection::importAutoCorrectionFile()
{
    mTempDir = new QTemporaryDir();
    const KArchiveDirectory *archiveDirectory = mArchive->directory();
    // Replace word
    if (!importFile(DOCUMENT, archiveDirectory)) {
        qCWarning(TEXTAUTOCORRECTION_LOG) << " Impossible to import DOCUMENT";
        return;
    }

    // No treat as end of line
    if (!importFile(SENTENCE, archiveDirectory)) {
        qCWarning(TEXTAUTOCORRECTION_LOG) << " Impossible to import SENTENCE";
        return;
    }

    // Two upper letter
    if (!importFile(WORD, archiveDirectory)) {
        qCWarning(TEXTAUTOCORRECTION_LOG) << " Impossible to import WORD";
        return;
    }
}

bool ImportLibreOfficeAutocorrection::importFile(Type type, const KArchiveDirectory *archiveDirectory)
{
    const KArchiveEntry *documentList = nullptr;

    QString archiveFileName;
    switch (type) {
    case DOCUMENT:
        archiveFileName = u"DocumentList.xml"_s;
        break;
    case SENTENCE:
        archiveFileName = u"SentenceExceptList.xml"_s;
        break;
    case WORD:
        archiveFileName = u"WordExceptList.xml"_s;
        break;
    default:
        return false;
    }
    documentList = archiveDirectory->entry(archiveFileName);
    if (!documentList) {
        qCWarning(TEXTAUTOCORRECTION_LOG) << "Archive doesn't have file: " << archiveFileName;
        return false;
    }
    if (documentList->isFile()) {
        const auto archiveFile = static_cast<const KArchiveFile *>(documentList);
        archiveFile->copyTo(mTempDir->path());
        QFile file(mTempDir->path() + u'/' + archiveFileName);
        if (!file.open(QIODevice::ReadOnly)) {
            qCWarning(TEXTAUTOCORRECTION_LOG) << "Impossible to open " << file.fileName();
        }
        QDomDocument doc;
        if (loadDomElement(doc, &file)) {
            QDomElement list = doc.documentElement();
            if (list.isNull()) {
                qCDebug(TEXTAUTOCORRECTION_LOG) << "No list defined in " << type;
            } else {
                for (QDomElement e = list.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()) {
                    const QString tag = e.tagName();
                    if (tag == "block-list:block"_L1) {
                        switch (type) {
                        case DOCUMENT:
                            if (e.hasAttribute(u"block-list:abbreviated-name"_s) && e.hasAttribute(u"block-list:name"_s)) {
                                const QString find = e.attribute(u"block-list:abbreviated-name"_s);
                                const QString replace = e.attribute(u"block-list:name"_s);
                                mAutocorrectEntries.insert(find, replace);
                                const int findLenght(find.length());
                                mMaxFindStringLength = qMax(findLenght, mMaxFindStringLength);
                                mMinFindStringLength = qMin(findLenght, mMinFindStringLength);
                            }
                            break;
                        case SENTENCE:
                            if (e.hasAttribute(u"block-list:abbreviated-name"_s)) {
                                mUpperCaseExceptions.insert(e.attribute(u"block-list:abbreviated-name"_s));
                            }

                            break;
                        case WORD:
                            if (e.hasAttribute(u"block-list:abbreviated-name"_s)) {
                                mTwoUpperLetterExceptions.insert(e.attribute(u"block-list:abbreviated-name"_s));
                            }
                            break;
                        }
                    } else {
                        qCDebug(TEXTAUTOCORRECTION_LOG) << " unknown tag " << tag;
                    }
                }
            }
        }
    } else {
        return false;
    }
    return true;
}

bool ImportLibreOfficeAutocorrection::loadDomElement(QDomDocument &doc, QFile *file)
{
    const QDomDocument::ParseResult parseResult = doc.setContent(file);
    if (!parseResult) {
        qCDebug(TEXTAUTOCORRECTION_LOG) << "Unable to load document.Parse error in line " << parseResult.errorLine << ", col " << parseResult.errorColumn
                                        << ": " << parseResult.errorMessage;
        return false;
    }
    return true;
}
