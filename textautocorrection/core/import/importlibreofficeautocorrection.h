/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "importabstractautocorrection.h"
#include "textautocorrectioncore_export.h"
class QTemporaryDir;
class KZip;
class QDomDocument;
class QFile;
class KArchiveDirectory;

namespace TextAutoCorrection
{
class TEXTAUTOCORRECTIONCORE_EXPORT ImportLibreOfficeAutocorrection : public ImportAbstractAutocorrection
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

    TEXTAUTOCORRECTIONCORE_NO_EXPORT void importAutoCorrectionFile();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void closeArchive();
    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT bool loadDomElement(QDomDocument &doc, QFile *file);
    Q_REQUIRED_RESULT TEXTAUTOCORRECTIONCORE_NO_EXPORT bool importFile(Type type, const KArchiveDirectory *archiveDirectory);
    KZip *mArchive = nullptr;
    QTemporaryDir *mTempDir = nullptr;
};
}
