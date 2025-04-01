/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratetextconfigurecombowidget.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogenerateengineutil.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QComboBox>
#include <QHBoxLayout>
#include <QToolButton>

using namespace TextAutogenerateText;
TextAutogenerateTextConfigureComboWidget::TextAutogenerateTextConfigureComboWidget(QWidget *parent)
    : QWidget{parent}
    , mEngineComboBox(new QComboBox(this))
    , mConfigureEngine(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mEngineComboBox->setObjectName(QStringLiteral("mEngineComboBox"));
    mainLayout->addWidget(mEngineComboBox);

    mConfigureEngine->setObjectName(QStringLiteral("mConfigureEngine"));
    mainLayout->addWidget(mConfigureEngine);
    mConfigureEngine->setEnabled(false); // Disable by default
    mConfigureEngine->setIcon(QIcon::fromTheme(QStringLiteral("settings-configure")));
    connect(mConfigureEngine, &QToolButton::clicked, this, &TextAutogenerateTextConfigureComboWidget::slotConfigureEngine);
    connect(mEngineComboBox, &QComboBox::currentIndexChanged, this, &TextAutogenerateTextConfigureComboWidget::slotEngineChanged);

    fillEngine();
}

TextAutogenerateTextConfigureComboWidget::~TextAutogenerateTextConfigureComboWidget() = default;

void TextAutogenerateTextConfigureComboWidget::slotConfigureEngine()
{
    const QString engine = mEngineComboBox->currentData().toString();
    if (TextAutogenerateText::TextAutogenerateEngineLoader::self()->hasConfigurationDialog(engine)) {
        if (TextAutogenerateText::TextAutogenerateEngineLoader::self()->showConfigureDialog(engine, this)) {
            Q_EMIT configureChanged(engine);
        }
    }
}

void TextAutogenerateTextConfigureComboWidget::fillEngine()
{
    TextAutogenerateText::TextAutogenerateEngineLoader::self()->loadPlugins();
    const QMap<QString, QString> map = TextAutogenerateText::TextAutogenerateEngineLoader::self()->textAutoGenerateTextEngineInfos();
    QMapIterator<QString, QString> iMap(map);
    while (iMap.hasNext()) {
        iMap.next();
        mEngineComboBox->addItem(iMap.value(), iMap.key());
    }
}

void TextAutogenerateTextConfigureComboWidget::slotEngineChanged(int index)
{
    const QString engine = mEngineComboBox->itemData(index).toString();
    mConfigureEngine->setEnabled(TextAutogenerateText::TextAutogenerateEngineLoader::self()->hasConfigurationDialog(engine));
    Q_EMIT engineChanged(engine);
}

void TextAutogenerateTextConfigureComboWidget::load()
{
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TextAutogenerateEngineUtil::groupAutoGenerateTextName());
    const QString engine = groupTranslate.readEntry(TextAutogenerateEngineUtil::engineTranslateName(), TextAutogenerateEngineUtil::defaultEngineName());
    const int index = mEngineComboBox->findData(engine);
    if (index != -1) {
        mEngineComboBox->setCurrentIndex(index);
    }
}

void TextAutogenerateTextConfigureComboWidget::save()
{
    const QString engine = mEngineComboBox->currentData().toString();
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TextAutogenerateEngineUtil::groupAutoGenerateTextName());
    groupTranslate.writeEntry(TextAutogenerateEngineUtil::engineTranslateName(), engine);
}

#include "moc_textautogeneratetextconfigurecombowidget.cpp"
