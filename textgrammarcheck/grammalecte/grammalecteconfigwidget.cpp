/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "grammalectemanager.h"
#include "grammalecteurlrequesterwidget.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTabWidget>
#include <QToolButton>
#include <QVBoxLayout>

using namespace TextGrammarCheck;
GrammalecteConfigWidget::GrammalecteConfigWidget(QWidget *parent, bool disableMessageBox)
    : QWidget(parent)
    , mDisableDialogBox(disableMessageBox)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});

    auto mTab = new QTabWidget(this);
    mTab->setObjectName(u"mTab"_s);
    mainLayout->addWidget(mTab);
    mTab->addTab(addGeneralTab(), i18n("General"));
    mTab->addTab(addGrammarTab(), i18n("Grammar Settings"));
    loadSettings(); // First
    loadGrammarSettings();
}

GrammalecteConfigWidget::~GrammalecteConfigWidget()
{
    saveSettings();
}

void GrammalecteConfigWidget::loadGrammarSettings()
{
    auto job = new GrammalecteGenerateConfigOptionJob(this);
    job->setPythonPath(mPythonPath->path());
    job->setGrammarlecteCliPath(mGrammalectePath->path());
    connect(job, &GrammalecteGenerateConfigOptionJob::finished, this, &GrammalecteConfigWidget::slotGetSettingsFinished);
    connect(job, &GrammalecteGenerateConfigOptionJob::error, this, &GrammalecteConfigWidget::slotGetSettingsError);
    job->start();
}

void GrammalecteConfigWidget::slotGetSettingsError()
{
    mStackedWidget->setCurrentWidget(mReloadSettingsWidget);
    if (!mDisableDialogBox) {
        KMessageBox::error(this,
                           i18n("Impossible to get options. Please verify that you have grammalected installed."),
                           i18nc("@title:window", "Error during Extracting Options"));
    }
}

void GrammalecteConfigWidget::slotGetSettingsFinished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result)
{
    mStackedWidget->setCurrentWidget(mScrollArea);
    mListOptions.clear();
    mListOptions.reserve(result.count());
    delete mGrammarTabWidget->layout();
    auto layout = new QVBoxLayout(mGrammarTabWidget);
    layout->setObjectName(u"grammartablayout"_s);

    for (const GrammalecteGenerateConfigOptionJob::Option &opt : result) {
        auto box = new QCheckBox(opt.description, this);
        box->setProperty("optionname", opt.optionName);
        if (mSaveOptions.isEmpty()) {
            box->setChecked(opt.defaultValue);
        } else {
            box->setChecked(mSaveOptions.contains(opt.optionName));
        }
        mGrammarTabWidget->layout()->addWidget(box);
        mListOptions.append(box);
    }
}

QWidget *GrammalecteConfigWidget::addGrammarTab()
{
    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->setObjectName(u"stackedwidget"_s);

    mScrollArea = new QScrollArea(this);
    mScrollArea->setObjectName(u"scrollarea"_s);
    mScrollArea->setWidgetResizable(true);
    mGrammarTabWidget = new QWidget;
    mGrammarTabWidget->setObjectName(u"grammar"_s);
    auto layout = new QVBoxLayout(mGrammarTabWidget);
    layout->setObjectName(u"grammartablayout"_s);
    mScrollArea->setWidget(mGrammarTabWidget);

    mStackedWidget->addWidget(mScrollArea);

    mReloadSettingsWidget = new QWidget;
    mReloadSettingsWidget->setObjectName(u"reloadwidget"_s);
    mStackedWidget->addWidget(mReloadSettingsWidget);
    auto reloadSettingsLayout = new QVBoxLayout(mReloadSettingsWidget);
    reloadSettingsLayout->setObjectName(u"reloadSettingsLayout"_s);
    auto horizontallayout = new QHBoxLayout;
    reloadSettingsLayout->addLayout(horizontallayout);
    auto label = new QLabel(i18nc("@label:textbox", "Press Button for Reloading Settings"), this);
    label->setTextFormat(Qt::PlainText);
    label->setObjectName(u"label"_s);
    horizontallayout->addWidget(label);

    auto buttonReloadSettings = new QToolButton(this);
    buttonReloadSettings->setIcon(QIcon::fromTheme(u"view-refresh"_s));
    buttonReloadSettings->setObjectName(u"buttonReloadSettings"_s);
    buttonReloadSettings->setToolTip(i18nc("@info:tooltip", "Reload Settings"));
    horizontallayout->addWidget(buttonReloadSettings);
    connect(buttonReloadSettings, &QToolButton::clicked, this, &GrammalecteConfigWidget::loadGrammarSettings);

    reloadSettingsLayout->addStretch(1);
    return mStackedWidget;
}

QWidget *GrammalecteConfigWidget::addGeneralTab()
{
    auto w = new QWidget(this);
    w->setObjectName(u"general"_s);
    auto lay = new QFormLayout(w);
    lay->setObjectName(u"generallayout"_s);

    mPythonPath = new TextGrammarCheck::GrammalecteUrlRequesterWidget(this);
    mPythonPath->setObjectName(u"pythonpath"_s);
    lay->addRow(i18n("Python Path:"), mPythonPath);

    mGrammalectePath = new TextGrammarCheck::GrammalecteUrlRequesterWidget(this);
    mGrammalectePath->setObjectName(u"grammalectepath"_s);
    mGrammalectePath->setPlaceholderText(i18nc("@info:placeholder", "Add full 'grammalecte-cli.py' path"));

    lay->addRow(i18n("Grammalecte Path:"), mGrammalectePath);

    auto grammalecteInfoDownload = new QLabel(this);
    grammalecteInfoDownload->setObjectName(u"grammalecteInfoDownload"_s);
    grammalecteInfoDownload->setTextFormat(Qt::RichText);
    grammalecteInfoDownload->setOpenExternalLinks(true);
    grammalecteInfoDownload->setText(i18n("Grammalecte can be found <a href=\"https://grammalecte.net/#download\">here</a>. Download it and extract it."));
    lay->addWidget(grammalecteInfoDownload);

    return w;
}

void GrammalecteConfigWidget::loadSettings()
{
    mPythonPath->setPath(GrammalecteManager::self()->pythonPath());
    mGrammalectePath->setPath(GrammalecteManager::self()->grammalectePath());
    mSaveOptions = GrammalecteManager::self()->options();
}

void GrammalecteConfigWidget::saveSettings()
{
    QStringList result;
    for (QCheckBox *checkBox : std::as_const(mListOptions)) {
        if (checkBox->isChecked()) {
            result += checkBox->property("optionname").toString();
        }
    }
    GrammalecteManager::self()->setPythonPath(mPythonPath->path());
    GrammalecteManager::self()->setGrammalectePath(mGrammalectePath->path());
    GrammalecteManager::self()->setOptions(result);
    GrammalecteManager::self()->saveSettings();
}

#include "moc_grammalecteconfigwidget.cpp"
