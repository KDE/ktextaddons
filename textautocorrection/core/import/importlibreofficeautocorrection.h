/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "importabstractautocorrection.h"
#include "textautocorrection_export.h"
class QTemporaryDir;
class KZip;
class QDomDocument;
class QFile;
class KArchiveDirectory;

namespace TextAutoCorrection
{
class TEXTAUTOCORRECTION_EXPORT ImportLibreOfficeAutocorrection : public ImportAbstractAutocorrection
{
public:
    ImportLibreOfficeAutocorrection();
    ~ImportLibreOfficeAutocorrection() override;

    Q_REQUIRED_RESULT bool import(const QString &fileName, QString &errorMessage, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) override;

private:
    enum Type {
        DOCUMENT,
        SENTENCE,
        WORD,
    };

    TEXTAUTOCORRECTION_NO_EXPORT void importAutoCorrectionFile();
    TEXTAUTOCORRECTION_NO_EXPORT void closeArchive();
    Q_REQUIRED_RESULT TEXTAUTOCORRECTION_NO_EXPORT bool loadDomElement(QDomDocument &doc, QFile *file);
    Q_REQUIRED_RESULT TEXTAUTOCORRECTION_NO_EXPORT bool importFile(Type type, const KArchiveDirectory *archiveDirectory);
    KZip *mArchive = nullptr;
    QTemporaryDir *mTempDir = nullptr;
};
}
