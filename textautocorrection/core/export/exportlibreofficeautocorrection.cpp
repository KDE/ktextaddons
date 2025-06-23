/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exportlibreofficeautocorrection.h"
#include "autocorrectionutils.h"
#include "textautocorrection_debug.h"
#include <KZip>
#include <QDir>
#include <QTemporaryFile>
#include <QXmlStreamWriter>

using namespace TextAutoCorrectionCore;
using namespace Qt::Literals::StringLiterals;
ExportLibreOfficeAutocorrection::ExportLibreOfficeAutocorrection() = default;

ExportLibreOfficeAutocorrection::~ExportLibreOfficeAutocorrection()
{
    delete mZip;
}

bool ExportLibreOfficeAutocorrection::exportData(const QString &language, const QString &fileName, QString &errorMessage, const QString &writablePath)
{
    Q_UNUSED(errorMessage);
    const QString libreOfficeWritableLocalAutoCorrectionPath =
        writablePath.isEmpty() ? AutoCorrectionUtils::libreOfficeWritableLocalAutoCorrectionPath() : writablePath;
    QDir().mkpath(libreOfficeWritableLocalAutoCorrectionPath);
    QString fixLangExtension = language;
    fixLangExtension.replace(u'_', u'-');
    const QString fname = fileName.isEmpty() ? libreOfficeWritableLocalAutoCorrectionPath + u"acor_%1.dat"_s.arg(fixLangExtension) : fileName;
    // qDebug() << " fname " << fname;
    mZip = new KZip(fname);
    const bool result = mZip->open(QIODevice::WriteOnly);
    if (!result) {
        qCWarning(TEXTAUTOCORRECTION_LOG) << "Impossible to open " << fileName;
        return false;
    }
    if (!exportDocumentList()) {
        return false;
    }
    if (!exportSentenceExceptList()) {
        return false;
    }
    if (!exportWordExceptList()) {
        return false;
    }
    if (!exportManifest()) {
        return false;
    }
    mZip->close();
    delete mZip;
    mZip = nullptr;
    return true;
}

bool ExportLibreOfficeAutocorrection::exportDocumentList()
{
    QTemporaryFile temporaryShareFile;
    temporaryShareFile.open();
    QXmlStreamWriter streamWriter(&temporaryShareFile);

    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeStartElement(u"block-list:block-list"_s);
    streamWriter.writeAttribute(u"xmlns:block-list"_s, u"http://openoffice.org/2001/block-list"_s);
    QHashIterator<QString, QString> i(mAutocorrectEntries);
    while (i.hasNext()) {
        i.next();
        streamWriter.writeStartElement(u"block-list:block"_s);
        streamWriter.writeAttribute(u"block-list:abbreviated-name"_s, i.key());
        streamWriter.writeAttribute(u"block-list:name"_s, i.value());
        streamWriter.writeEndElement();
    }
    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    temporaryShareFile.close();
    mZip->addLocalFile(temporaryShareFile.fileName(), u"DocumentList.xml"_s);
    return true;
}

bool ExportLibreOfficeAutocorrection::exportSentenceExceptList()
{
    QTemporaryFile temporaryShareFile;
    temporaryShareFile.open();

    QXmlStreamWriter streamWriter(&temporaryShareFile);

    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeStartElement(u"block-list:block-list"_s);
    streamWriter.writeAttribute(u"xmlns:block-list"_s, u"http://openoffice.org/2001/block-list"_s);

    QSet<QString>::const_iterator upper = mUpperCaseExceptions.constBegin();
    while (upper != mUpperCaseExceptions.constEnd()) {
        streamWriter.writeStartElement(u"block-list:block"_s);
        streamWriter.writeAttribute(u"block-list:abbreviated-name"_s, *upper);
        streamWriter.writeEndElement();
        ++upper;
    }
    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    temporaryShareFile.close();

    mZip->addLocalFile(temporaryShareFile.fileName(), u"SentenceExceptList.xml"_s);
    return true;
}

bool ExportLibreOfficeAutocorrection::exportWordExceptList()
{
    QTemporaryFile temporaryShareFile;
    temporaryShareFile.open();

    QXmlStreamWriter streamWriter(&temporaryShareFile);

    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeStartElement(u"block-list:block-list"_s);
    streamWriter.writeAttribute(u"xmlns:block-list"_s, u"http://openoffice.org/2001/block-list"_s);

    QSet<QString>::const_iterator twoUpper = mTwoUpperLetterExceptions.constBegin();
    while (twoUpper != mTwoUpperLetterExceptions.constEnd()) {
        streamWriter.writeStartElement(u"block-list:block"_s);
        streamWriter.writeAttribute(u"block-list:abbreviated-name"_s, *twoUpper);
        streamWriter.writeEndElement();
        ++twoUpper;
    }
    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    temporaryShareFile.close();

    mZip->addLocalFile(temporaryShareFile.fileName(), u"WordExceptList.xml"_s);
    return true;
}

bool ExportLibreOfficeAutocorrection::exportManifest()
{
    QTemporaryFile temporaryShareFile;
    temporaryShareFile.open();

    QXmlStreamWriter streamWriter(&temporaryShareFile);
    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeStartElement(u"manifest:manifest"_s);

    streamWriter.writeStartElement(u"manifest:file-entry"_s);
    streamWriter.writeAttribute(u"manifest:full-path"_s, u"/"_s);
    streamWriter.writeAttribute(u"manifest:media-type"_s, QString());
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(u"manifest:file-entry"_s);
    streamWriter.writeAttribute(u"manifest:full-path"_s, u"DocumentList.xml"_s);
    streamWriter.writeAttribute(u"manifest:media-type"_s, QString());
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(u"manifest:file-entry"_s);
    streamWriter.writeAttribute(u"manifest:full-path"_s, u"SentenceExceptList.xml"_s);
    streamWriter.writeAttribute(u"manifest:media-type"_s, QString());
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(u"manifest:file-entry"_s);
    streamWriter.writeAttribute(u"manifest:full-path"_s, u"WordExceptList.xml"_s);
    streamWriter.writeAttribute(u"manifest:media-type"_s, u"text/xml"_s);
    streamWriter.writeEndElement();

    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    temporaryShareFile.close();

    // Add mimetype file
    mZip->setCompression(KZip::NoCompression);
    mZip->writeFile(u"mimetype"_s, "");
    mZip->setCompression(KZip::DeflateCompression);
    mZip->addLocalFile(temporaryShareFile.fileName(), u"META-INF/manifest.xml"_s);
    return true;
}
