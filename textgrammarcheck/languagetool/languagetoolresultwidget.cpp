/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolresultwidget.h"
#include "common/grammarresulttextedit.h"
#include "languagetoolcombobox.h"
#include "languagetoolmanager.h"
#include "languagetoolparser.h"
#include "languagetoolresultjob.h"
#include "languagetoolupdatecombobox.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <QHBoxLayout>
#include <QJsonDocument>
#include <QToolButton>
using namespace TextGrammarCheck;
LanguageToolResultWidget::LanguageToolResultWidget(QWidget *parent)
    : GrammarResultWidget(parent)
    , mLanguageToolUpdateCombobox(new LanguageToolUpdateComboBox(this))
{
    addExtraWidget();
    mLanguageToolUpdateCombobox->setLanguageToolCombobox(mLanguageToolComboBox);
    mLanguageToolUpdateCombobox->setParentWidget(this);
    if (LanguageToolManager::self()->allowToGetListOfLanguages()) {
        mLanguageToolUpdateCombobox->firstRefreshListOfLanguages();
    } else {
        mLanguageToolComboBox->setLanguage(LanguageToolManager::self()->language());
    }
}

LanguageToolResultWidget::~LanguageToolResultWidget() = default;

void LanguageToolResultWidget::checkGrammar()
{
    auto job = new LanguageToolResultJob(this);
    job->setUrl(LanguageToolManager::self()->languageToolCheckPath());
    job->setNetworkAccessManager(LanguageToolManager::self()->networkAccessManager());
    job->setText(mResult->toPlainText());
    job->setLanguage(/*LanguageToolManager::self()->language()*/ mLanguageToolComboBox->language());
    connect(job, &LanguageToolResultJob::finished, this, &LanguageToolResultWidget::slotCheckGrammarFinished);
    connect(job, &LanguageToolResultJob::error, this, &LanguageToolResultWidget::slotError);
    job->start();
}

void LanguageToolResultWidget::slotCheckGrammarFinished(const QString &result)
{
    LanguageToolParser parser;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonObject fields = doc.object();
    applyGrammarResult(parser.parseResult(fields));
}

void LanguageToolResultWidget::slotError(const QString &str)
{
    KMessageBox::error(this, i18n("An error was reported: %1", str), i18n("Failed to check grammar."));
}

void LanguageToolResultWidget::addExtraWidget()
{
    auto extraWidgetLayout = new QHBoxLayout;
    extraWidgetLayout->setObjectName(QStringLiteral("extraWidgetLayout"));
    extraWidgetLayout->setContentsMargins({});
    mLanguageToolComboBox = new LanguageToolComboBox(this);
    mLanguageToolComboBox->setObjectName(QStringLiteral("languagetoolcombobox"));
    extraWidgetLayout->addWidget(mLanguageToolComboBox);

    auto recheckBtn = new QToolButton(this);
    recheckBtn->setObjectName(QStringLiteral("recheck-button"));
    recheckBtn->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
    recheckBtn->setIconSize(QSize(16, 16));
    recheckBtn->setToolTip(i18n("Check"));
    recheckBtn->setAutoRaise(true);
    extraWidgetLayout->addWidget(recheckBtn);

    mExtraWidgetLayout->addLayout(extraWidgetLayout);
    connect(recheckBtn, &QToolButton::clicked, this, &LanguageToolResultWidget::checkAgain);
}

#include "moc_languagetoolresultwidget.cpp"
