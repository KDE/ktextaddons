/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

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
    void loadGrammarSettings();
    void slotGetSettingsFinished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result);
    void slotGetSettingsError();

    QStringList mSaveOptions;
    QVector<QCheckBox *> mListOptions;
    QWidget *addGeneralTab();
    QWidget *addGrammarTab();
    QStackedWidget *mStackedWidget = nullptr;
    QWidget *mGrammarTabWidget = nullptr;
    QWidget *mReloadSettingsWidget = nullptr;
    QScrollArea *mScrollArea = nullptr;
    GrammalecteUrlRequesterWidget *mPythonPath = nullptr;
    GrammalecteUrlRequesterWidget *mGrammalectePath = nullptr;
    const bool mDisableDialogBox = false;
};
}
