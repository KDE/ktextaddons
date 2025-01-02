/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

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
class TEXTGRAMMARCHECK_EXPORT GrammalecteConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammalecteConfigWidget(QWidget *parent = nullptr, bool disableMessageBox = false);
    ~GrammalecteConfigWidget() override;
    void loadSettings();
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
