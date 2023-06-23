/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importexportautocorrectionlibreofficetest.h"
#include "export/exportlibreofficeautocorrection.h"
#include "import/importlibreofficeautocorrection.h"
#include <QStandardPaths>
#include <QTemporaryFile>
#include <QTest>

QTEST_MAIN(ImportExportAutocorrectionLibreOfficeTest)
ImportExportAutocorrectionLibreOfficeTest::ImportExportAutocorrectionLibreOfficeTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void ImportExportAutocorrectionLibreOfficeTest::shouldImportExport()
{
    QFETCH(QString, filename);

    const QString originalFile = QLatin1String(AUTOCORRECTION_DATA_DIR) + QLatin1Char('/') + filename;

    // First step
    TextAutoCorrectionCore::ImportLibreOfficeAutocorrection import;
    QString messageError;
    if (import.import(originalFile, messageError, TextAutoCorrectionCore::ImportAbstractAutocorrection::All)) {
        const auto mUpperCaseExceptions = import.upperCaseExceptions();
        const auto mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
        const auto mAutocorrectEntries = import.autocorrectEntries();

        // Test export
        TextAutoCorrectionCore::ExportLibreOfficeAutocorrection correct;
        correct.setAutocorrectEntries(mAutocorrectEntries);
        correct.setUpperCaseExceptions(mUpperCaseExceptions);
        correct.setTwoUpperLetterExceptions(mTwoUpperLetterExceptions);
        QString message;

        QTemporaryFile temporaryShareFile;
        temporaryShareFile.open();

        if (!correct.exportData(QString(), temporaryShareFile.fileName(), message, QString())) {
            QVERIFY(false);
            qWarning() << "We can't save in file :" << temporaryShareFile.fileName();
        }
        // Close temporary file
        temporaryShareFile.close();

        // Reimport
        TextAutoCorrectionCore::ImportLibreOfficeAutocorrection importTwoStep;
        if (import.import(temporaryShareFile.fileName(), messageError, TextAutoCorrectionCore::ImportAbstractAutocorrection::All)) {
            const auto mUpperCaseExceptionsStep2 = import.upperCaseExceptions();
            const auto mTwoUpperLetterExceptionsStep2 = import.twoUpperLetterExceptions();
            const auto mAutocorrectEntriesStep2 = import.autocorrectEntries();
            QCOMPARE(mUpperCaseExceptionsStep2, mUpperCaseExceptions);
            QCOMPARE(mTwoUpperLetterExceptionsStep2, mTwoUpperLetterExceptions);
            QCOMPARE(mAutocorrectEntriesStep2, mAutocorrectEntries);
        } else {
            qWarning() << "Impossible to import " << temporaryShareFile.fileName();
            QVERIFY(false);
        }
    } else {
        qWarning() << "Impossible to import " << originalFile;
        QVERIFY(false);
    }
}

void ImportExportAutocorrectionLibreOfficeTest::shouldImportExport_data()
{
    QTest::addColumn<QString>("filename");
    QTest::newRow("disable") << QStringLiteral("acor_fr.dat");
}

#include "moc_importexportautocorrectionlibreofficetest.cpp"
