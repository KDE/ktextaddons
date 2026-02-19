/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QWidget>
#include <TextGrammarCheck/GrammalecteGenerateConfigOptionJob>
class QCheckBox;
class QStackedWidget;
class QScrollArea;
namespace TextGrammarCheck
{
class GrammalecteUrlRequesterWidget;
/*!
 * \class TextGrammarCheck::GrammalecteConfigWidget
 * \inheaderfile TextGrammarCheck/GrammalecteConfigWidget
 * \inmodule TextGrammarCheck
 * \brief Configuration widget for Grammalecte grammar checker.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammalecteConfigWidget : public QWidget
{
    Q_OBJECT
public:
    /*! Constructs a new GrammalecteConfigWidget. */
    explicit GrammalecteConfigWidget(QWidget *parent = nullptr, bool disableMessageBox = false);
    /*! Destroys the widget. */
    ~GrammalecteConfigWidget() override;
    /*! Loads the current settings from the configuration. */
    void loadSettings();
    /*! Saves the current settings to the configuration. */
    void saveSettings();

private:
    Q_DISABLE_COPY(GrammalecteConfigWidget)
    TEXTGRAMMARCHECK_NO_EXPORT void loadGrammarSettings();
    TEXTGRAMMARCHECK_NO_EXPORT void slotGetSettingsFinished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result);
    TEXTGRAMMARCHECK_NO_EXPORT void slotGetSettingsError();
    TEXTGRAMMARCHECK_NO_EXPORT QWidget *addGeneralTab();
    TEXTGRAMMARCHECK_NO_EXPORT QWidget *addGrammarTab();

    QStringList mSaveOptions;
    QVector<QCheckBox *> mListOptions;
    QStackedWidget *mStackedWidget = nullptr;
    QWidget *mGrammarTabWidget = nullptr;
    QWidget *mReloadSettingsWidget = nullptr;
    QScrollArea *mScrollArea = nullptr;
    GrammalecteUrlRequesterWidget *mPythonPath = nullptr;
    GrammalecteUrlRequesterWidget *mGrammalectePath = nullptr;
    const bool mDisableDialogBox = false;
};
}
