/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "autocorrection.h"
#include "textautocorrection_export.h"
#include <QWidget>

class QTreeWidgetItem;

namespace Ui
{
class AutoCorrectionWidget;
}

namespace TextAutoCorrection
{
class AutoCorrectionWidgetPrivate;
/**
 * @brief The AutoCorrectionWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTION_EXPORT AutoCorrectionWidget : public QWidget
{
    Q_OBJECT

public:
    enum ImportFileType {
        LibreOffice,
        KMail,
    };

    explicit AutoCorrectionWidget(QWidget *parent = nullptr);
    ~AutoCorrectionWidget() override;
    void setAutoCorrection(AutoCorrection *autoCorrect);
    void setHasHtmlSupport(bool b);
    void loadConfig();
    void writeConfig();
    void resetToDefault();

Q_SIGNALS:
    void changed();

private:
    /* tab 2 */
    TEXTAUTOCORRECTION_NO_EXPORT void enableSingleQuotes(bool state);
    TEXTAUTOCORRECTION_NO_EXPORT void enableDoubleQuotes(bool state);
    TEXTAUTOCORRECTION_NO_EXPORT void selectSingleQuoteCharOpen();
    TEXTAUTOCORRECTION_NO_EXPORT void selectSingleQuoteCharClose();
    TEXTAUTOCORRECTION_NO_EXPORT void setDefaultSingleQuotes();
    TEXTAUTOCORRECTION_NO_EXPORT void selectDoubleQuoteCharOpen();
    TEXTAUTOCORRECTION_NO_EXPORT void selectDoubleQuoteCharClose();
    TEXTAUTOCORRECTION_NO_EXPORT void setDefaultDoubleQuotes();

    /* tab 3 */
    TEXTAUTOCORRECTION_NO_EXPORT void enableAdvAutocorrection(bool state);
    TEXTAUTOCORRECTION_NO_EXPORT void addAutocorrectEntry();
    TEXTAUTOCORRECTION_NO_EXPORT void removeAutocorrectEntry();
    TEXTAUTOCORRECTION_NO_EXPORT void setFindReplaceText(QTreeWidgetItem *, int);
    TEXTAUTOCORRECTION_NO_EXPORT void enableAddRemoveButton();

    /* tab 4 */
    TEXTAUTOCORRECTION_NO_EXPORT void abbreviationChanged(const QString &text);
    TEXTAUTOCORRECTION_NO_EXPORT void twoUpperLetterChanged(const QString &text);
    TEXTAUTOCORRECTION_NO_EXPORT void addAbbreviationEntry();
    TEXTAUTOCORRECTION_NO_EXPORT void removeAbbreviationEntry();
    TEXTAUTOCORRECTION_NO_EXPORT void addTwoUpperLetterEntry();
    TEXTAUTOCORRECTION_NO_EXPORT void removeTwoUpperLetterEntry();

    TEXTAUTOCORRECTION_NO_EXPORT void slotEnableDisableAbreviationList();
    TEXTAUTOCORRECTION_NO_EXPORT void slotEnableDisableTwoUpperEntry();

    TEXTAUTOCORRECTION_NO_EXPORT void slotImportAutoCorrection(QAction *act);

    TEXTAUTOCORRECTION_NO_EXPORT void changeLanguage(int);
    TEXTAUTOCORRECTION_NO_EXPORT void updateAddRemoveButton();

    TEXTAUTOCORRECTION_NO_EXPORT void slotExportAutoCorrection();

private:
    TEXTAUTOCORRECTION_NO_EXPORT void slotChangeComboboxState(int index);
    TEXTAUTOCORRECTION_NO_EXPORT void emitChanged();
    TEXTAUTOCORRECTION_NO_EXPORT void addAutoCorrectEntries();
    TEXTAUTOCORRECTION_NO_EXPORT void loadAutoCorrectionAndException();
    TEXTAUTOCORRECTION_NO_EXPORT void loadGlobalAutoCorrectionAndException();
    TEXTAUTOCORRECTION_NO_EXPORT void setLanguage(const QString &lang);
    TEXTAUTOCORRECTION_NO_EXPORT void updateHtmlSupport();

    std::unique_ptr<AutoCorrectionWidgetPrivate> const d;
};
}
