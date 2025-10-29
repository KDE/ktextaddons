/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatorconfigurecombowidget.h"
using namespace Qt::Literals::StringLiterals;

#include "translator/misc/translatorutil.h"
#include "translator/translatorengineloader.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QComboBox>
#include <QHBoxLayout>
#include <QToolButton>

using namespace TextTranslator;
TranslatorConfigureComboWidget::TranslatorConfigureComboWidget(QWidget *parent)
    : QWidget{parent}
    , mEngineComboBox(new QComboBox(this))
    , mConfigureEngine(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mEngineComboBox->setObjectName(u"mEngineComboBox"_s);
    mainLayout->addWidget(mEngineComboBox);

    mConfigureEngine->setObjectName(u"mConfigureEngine"_s);
    mainLayout->addWidget(mConfigureEngine);
    mConfigureEngine->setEnabled(false); // Disable by default
    mConfigureEngine->setIcon(QIcon::fromTheme(u"settings-configure"_s));
    connect(mConfigureEngine, &QToolButton::clicked, this, &TranslatorConfigureComboWidget::slotConfigureEngine);
    connect(mEngineComboBox, &QComboBox::currentIndexChanged, this, &TranslatorConfigureComboWidget::slotEngineChanged);

    fillEngine();
}

TranslatorConfigureComboWidget::~TranslatorConfigureComboWidget() = default;

void TranslatorConfigureComboWidget::slotConfigureEngine()
{
    const QString engine = mEngineComboBox->currentData().toString();
    if (TextTranslator::TranslatorEngineLoader::self()->hasConfigurationDialog(engine)) {
        if (TextTranslator::TranslatorEngineLoader::self()->showConfigureDialog(engine, this)) {
            Q_EMIT configureChanged(engine);
        }
    }
}

void TranslatorConfigureComboWidget::fillEngine()
{
    for (const auto &[key, value] : TextTranslator::TranslatorEngineLoader::self()->translatorEngineInfos().asKeyValueRange()) {
        mEngineComboBox->addItem(value, key);
    }
}

void TranslatorConfigureComboWidget::slotEngineChanged(int index)
{
    const QString engine = mEngineComboBox->itemData(index).toString();
    mConfigureEngine->setEnabled(TextTranslator::TranslatorEngineLoader::self()->hasConfigurationDialog(engine));
    Q_EMIT engineChanged(engine);
}

void TranslatorConfigureComboWidget::load()
{
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TranslatorUtil::groupTranslateName());
    const QString engine = groupTranslate.readEntry(TranslatorUtil::engineTranslateName(), TranslatorUtil::defaultEngineName()); // Google by default
    const int index = mEngineComboBox->findData(engine);
    if (index != -1) {
        mEngineComboBox->setCurrentIndex(index);
    }
}

void TranslatorConfigureComboWidget::save()
{
    const QString engine = mEngineComboBox->currentData().toString();
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TranslatorUtil::groupTranslateName());
    groupTranslate.writeEntry(TranslatorUtil::engineTranslateName(), engine);
}

#include "moc_translatorconfigurecombowidget.cpp"
