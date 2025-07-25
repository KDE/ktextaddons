/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "languagetoolcombobox.h"
#include "languagetoolmanager.h"
#include "languagetoolupdatecombobox.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>
using namespace TextGrammarCheck;
LanguageToolConfigWidget::LanguageToolConfigWidget(QWidget *parent)
    : QWidget(parent)
    , mUseLocalInstance(new QCheckBox(i18nc("@option:check", "Use Local Instance"), this))
    , mInstancePath(new QLineEdit(this))
    , mInstancePathLabel(new QLabel(i18nc("@label:textbox", "Instance Path:"), this))
    , mLanguageToolCombobox(new LanguageToolComboBox(this))
    , mLanguageToolUpdateCombobox(new LanguageToolUpdateComboBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});

    mUseLocalInstance->setObjectName(u"uselocalinstance"_s);
    mainLayout->addWidget(mUseLocalInstance);

    auto instanceLayout = new QHBoxLayout;
    instanceLayout->setObjectName(u"instancelayout"_s);
    instanceLayout->setContentsMargins({});
    mInstancePathLabel->setObjectName(u"instancepath"_s);
    mInstancePathLabel->setEnabled(false);
    mInstancePathLabel->setTextFormat(Qt::PlainText);
    instanceLayout->addWidget(mInstancePathLabel);

    mInstancePath->setObjectName(u"instancepath"_s);
    mInstancePath->setEnabled(false);
    mInstancePath->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mInstancePath);
    instanceLayout->addWidget(mInstancePath);
    mainLayout->addLayout(instanceLayout);

    connect(mUseLocalInstance, &QCheckBox::clicked, this, &LanguageToolConfigWidget::updateWidgets);

    auto languageLayout = new QHBoxLayout;
    languageLayout->setObjectName(u"languagelayout"_s);
    auto languageLabel = new QLabel(i18nc("@label:textbox", "Language:"), this);
    languageLabel->setTextFormat(Qt::PlainText);
    languageLabel->setObjectName(u"languageLabel"_s);
    languageLayout->addWidget(languageLabel);

    mLanguageToolCombobox->setObjectName(u"languagecombobox"_s);
    languageLayout->addWidget(mLanguageToolCombobox);
    mLanguageToolUpdateCombobox->setLanguageToolCombobox(mLanguageToolCombobox);
    mLanguageToolUpdateCombobox->setParentWidget(this);

    auto refreshButton = new QToolButton(this);
    refreshButton->setObjectName(u"refreshbutton"_s);
    refreshButton->setIcon(QIcon::fromTheme(u"view-refresh"_s));
    refreshButton->setToolTip(i18nc("@info:tooltip", "Refresh"));
    if (!LanguageToolManager::self()->allowToGetListOfLanguages()) {
        refreshButton->setVisible(false);
    }
    languageLayout->addWidget(refreshButton);
    connect(refreshButton, &QToolButton::clicked, this, [this]() {
        if (LanguageToolManager::self()->allowToGetListOfLanguages()) {
            mLanguageToolUpdateCombobox->checkListOfLanguagesFromSpecificPath(LanguageToolManager::convertToLanguagePath(mInstancePath->text()));
        }
    });

    mainLayout->addLayout(languageLayout);

    mainLayout->addStretch(1);
    mLanguageToolUpdateCombobox->refreshListOfLanguages();
    loadSettings();
    updateWidgets(mUseLocalInstance->isChecked());
    connect(this, &LanguageToolConfigWidget::resetValue, this, &LanguageToolConfigWidget::slotResetValue);
}

LanguageToolConfigWidget::~LanguageToolConfigWidget()
{
    saveSettings();
}

void LanguageToolConfigWidget::slotResetValue()
{
    mUseLocalInstance->setChecked(false);
    mInstancePath->setText(u"https://api.languagetoolplus.com/v2"_s);
    updateWidgets(false);
}

void LanguageToolConfigWidget::updateWidgets(bool enabled)
{
    mInstancePathLabel->setEnabled(enabled);
    mInstancePath->setEnabled(enabled);
}

void LanguageToolConfigWidget::loadSettings()
{
    mUseLocalInstance->setChecked(LanguageToolManager::self()->useLocalInstance());
    mInstancePath->setText(LanguageToolManager::self()->languageToolPath());
    mLanguageToolCombobox->setLanguage(LanguageToolManager::self()->language());
}

void LanguageToolConfigWidget::saveSettings()
{
    LanguageToolManager::self()->setUseLocalInstance(mUseLocalInstance->isChecked());
    LanguageToolManager::self()->setLanguageToolPath(mInstancePath->text());
    LanguageToolManager::self()->setLanguage(mLanguageToolCombobox->language());
    LanguageToolManager::self()->saveSettings();
}

#include "moc_languagetoolconfigwidget.cpp"
