/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "exportabstractautocorrection.h"
#include "textautocorrectioncore_private_export.h"
class KZip;
namespace TextAutoCorrectionCore
{
class TEXTAUTOCORRECTIONCORE_TESTS_EXPORT ExportLibreOfficeAutocorrection : public ExportAbstractAutocorrection
{
public:
    ExportLibreOfficeAutocorrection();
    ~ExportLibreOfficeAutocorrection() override;

    [[nodiscard]] bool exportData(const QString &language, const QString &fileName, QString &errorMessage, const QString &writablePath) override;

private:
    [[nodiscard]] bool exportDocumentList();
    [[nodiscard]] bool exportSentenceExceptList();
    [[nodiscard]] bool exportWordExceptList();
    [[nodiscard]] bool exportManifest();
    KZip *mZip = nullptr;
};
}
