/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

using namespace Qt::Literals::StringLiterals;

#include "translatorconfigurelistswidget.h"
#include "translator/misc/translatorutil.h"
#include "translator/translatorengineloader.h"
#include "translatorconfigurecombowidget.h"
#include "translatorconfigurelanguagelistwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QLabel>
#include <QVBoxLayout>
using namespace TextTranslator;
class Q_DECL_HIDDEN TextTranslator::TranslatorConfigureListsWidget::TranslatorConfigureListsWidgetPrivate
{
public:
    TranslatorConfigureListsWidgetPrivate(TranslatorConfigureListsWidget *parent)
        : mEngineConfigureComboWidget(new TranslatorConfigureComboWidget(parent))
        , mFromLanguageWidget(new TranslatorConfigureLanguageListWidget(i18n("From:"), parent))
        , mToLanguageWidget(new TranslatorConfigureLanguageListWidget(i18n("To:"), parent))
    {
    }
    bool mLanguageListLoaded = false;
    TranslatorConfigureComboWidget *const mEngineConfigureComboWidget;
    TextTranslator::TranslatorConfigureLanguageListWidget *const mFromLanguageWidget;
    TextTranslator::TranslatorConfigureLanguageListWidget *const mToLanguageWidget;
};

TranslatorConfigureListsWidget::TranslatorConfigureListsWidget(QWidget *parent)
    : QWidget{parent}
    , d(new TranslatorConfigureListsWidgetPrivate(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    d->mEngineConfigureComboWidget->setObjectName(u"mEngineConfigureComboWidget"_s);
    connect(d->mEngineConfigureComboWidget,
            &TranslatorConfigureComboWidget::configureChanged,
            this,
            &TranslatorConfigureListsWidget::slotEngineSettingsChanged);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(u"hboxLayout"_s);
    hboxLayout->setContentsMargins({});
    mainLayout->addLayout(hboxLayout);

    auto label = new QLabel(i18nc("@label:textbox", "Engine:"), this);
    label->setObjectName(u"label"_s);
    label->setTextFormat(Qt::PlainText);
    hboxLayout->addWidget(label);
    hboxLayout->addWidget(d->mEngineConfigureComboWidget);
    hboxLayout->addStretch(0);

    auto hLanguageListboxLayout = new QHBoxLayout;
    hLanguageListboxLayout->setObjectName(u"hLanguageListboxLayout"_s);
    hLanguageListboxLayout->setContentsMargins({});
    mainLayout->addLayout(hLanguageListboxLayout);

    d->mFromLanguageWidget->setObjectName(u"mFromLanguageWidget"_s);
    d->mToLanguageWidget->setObjectName(u"mToLanguageWidget"_s);
    hLanguageListboxLayout->addWidget(d->mFromLanguageWidget);
    hLanguageListboxLayout->addWidget(d->mToLanguageWidget);

    connect(d->mEngineConfigureComboWidget, &TranslatorConfigureComboWidget::engineChanged, this, &TranslatorConfigureListsWidget::slotEngineChanged);
}

TranslatorConfigureListsWidget::~TranslatorConfigureListsWidget() = default;

void TranslatorConfigureListsWidget::save()
{
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TranslatorUtil::groupTranslateName());
    groupTranslate.writeEntry(u"From"_s, d->mFromLanguageWidget->selectedLanguages());
    groupTranslate.writeEntry(u"To"_s, d->mToLanguageWidget->selectedLanguages());
    d->mEngineConfigureComboWidget->save();
}

void TranslatorConfigureListsWidget::load()
{
    d->mEngineConfigureComboWidget->load();
}

void TranslatorConfigureListsWidget::slotEngineSettingsChanged(const QString &engineName)
{
    slotEngineChanged(engineName);
}

void TranslatorConfigureListsWidget::loadLanguagesList()
{
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TranslatorUtil::groupTranslateName());
    const auto fromLanguages = groupTranslate.readEntry(u"From"_s, QStringList());
    const auto toLanguages = groupTranslate.readEntry(u"To"_s, QStringList());
    d->mFromLanguageWidget->setSelectedLanguages(fromLanguages);
    d->mToLanguageWidget->setSelectedLanguages(toLanguages);
}

void TranslatorConfigureListsWidget::fillFromToLanguages(const QMap<TextTranslator::TranslatorUtil::Language, QString> &listFromLanguage,
                                                         const QMap<TextTranslator::TranslatorUtil::Language, QString> &listToLanguage)
{
    TranslatorUtil translatorUtil;
    for (const auto &[key, value] : listFromLanguage.asKeyValueRange()) {
        const QString languageCode = TranslatorUtil::languageCode(key);
        d->mFromLanguageWidget->addItem(value, languageCode);
    }

    for (const auto &[key, value] : listToLanguage.asKeyValueRange()) {
        const QString languageCode = TranslatorUtil::languageCode(key);
        d->mToLanguageWidget->addItem(value, languageCode);
    }
}

void TranslatorConfigureListsWidget::fillLanguages(const QMap<TextTranslator::TranslatorUtil::Language, QString> &listLanguage)
{
    TranslatorUtil translatorUtil;
    for (const auto &[key, value] : listLanguage.asKeyValueRange()) {
        const QString languageCode = TranslatorUtil::languageCode(key);
        d->mFromLanguageWidget->addItem(value, languageCode);
        if ((key != TranslatorUtil::automatic)) {
            d->mToLanguageWidget->addItem(value, languageCode);
        }
    }
}

void TranslatorConfigureListsWidget::slotEngineChanged(const QString &engine)
{
    const QMap<TextTranslator::TranslatorUtil::Language, QString> listFromLanguage =
        TextTranslator::TranslatorEngineLoader::self()->supportedFromLanguages(engine);
    const QMap<TextTranslator::TranslatorUtil::Language, QString> listToLanguage = TextTranslator::TranslatorEngineLoader::self()->supportedToLanguages(engine);

    if (!d->mLanguageListLoaded) {
        fillLanguages(listFromLanguage);
        loadLanguagesList();
        d->mLanguageListLoaded = true;
    } else {
        const QStringList fromLanguages = d->mFromLanguageWidget->selectedLanguages();
        const QStringList toLanguages = d->mToLanguageWidget->selectedLanguages();

        d->mFromLanguageWidget->clear();
        d->mToLanguageWidget->clear();
        if (listFromLanguage != listToLanguage) {
            fillFromToLanguages(listFromLanguage, listToLanguage);
        } else {
            fillLanguages(listFromLanguage);
        }

        // Restore if possible
        d->mFromLanguageWidget->setSelectedLanguages(fromLanguages);
        d->mToLanguageWidget->setSelectedLanguages(toLanguages);
    }
}

#include "moc_translatorconfigurelistswidget.cpp"
