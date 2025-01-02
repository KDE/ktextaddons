/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautocorrectionwidgets_export.h"
#include <QWidget>
#include <TextAutoCorrectionCore/AutoCorrection>

class QTreeWidgetItem;

namespace Ui
{
class AutoCorrectionWidget;
}

namespace TextAutoCorrectionWidgets
{
class AutoCorrectionWidgetPrivate;
/**
 * @brief The AutoCorrectionWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONWIDGETS_EXPORT AutoCorrectionWidget : public QWidget
{
    Q_OBJECT

public:
    enum ImportFileType {
        LibreOffice,
        KMail,
    };

    explicit AutoCorrectionWidget(QWidget *parent = nullptr);
    ~AutoCorrectionWidget() override;
    void setAutoCorrection(TextAutoCorrectionCore::AutoCorrection *autoCorrect);
    void setHasHtmlSupport(bool b);
    void loadConfig();
    void writeConfig();
    void resetToDefault();

Q_SIGNALS:
    void changed();

private:
    /* tab 2 */
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void enableSingleQuotes(bool state);
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void enableDoubleQuotes(bool state);
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void selectSingleQuoteCharOpen();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void selectSingleQuoteCharClose();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void setDefaultSingleQuotes();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void selectDoubleQuoteCharOpen();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void selectDoubleQuoteCharClose();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void setDefaultDoubleQuotes();

    /* tab 3 */
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void enableAdvAutocorrection(bool state);
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void addAutocorrectEntry();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void removeAutocorrectEntry();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void setFindReplaceText(QTreeWidgetItem *, int);
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void enableAddRemoveButton();

    /* tab 4 */
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void abbreviationChanged(const QString &text);
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void twoUpperLetterChanged(const QString &text);
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void addAbbreviationEntry();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void removeAbbreviationEntry();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void addTwoUpperLetterEntry();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void removeTwoUpperLetterEntry();

    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void slotEnableDisableAbreviationList();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void slotEnableDisableTwoUpperEntry();

    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void slotImportAutoCorrection(QAction *act);

    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void changeLanguage();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void updateAddRemoveButton();

    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void slotExportAutoCorrection();

private:
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void slotChangeComboboxState(int index);
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void emitChanged();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void addAutoCorrectEntries();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void loadAutoCorrectionAndException();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void loadGlobalAutoCorrectionAndException();
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void setLanguage(const QString &lang);
    TEXTAUTOCORRECTIONWIDGETS_NO_EXPORT void updateHtmlSupport();

    std::unique_ptr<AutoCorrectionWidgetPrivate> const d;
};
}
