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

using namespace TextAutoGenerateText;
TextAutoGenerateTextConfigureComboWidget::TextAutoGenerateTextConfigureComboWidget(QWidget *parent)
    : QWidget{parent}
    , mEngineComboBox(new QComboBox(this))
    , mConfigureEngine(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);

    mEngineComboBox->setObjectName(QStringLiteral("mEngineComboBox"));
    mainLayout->addWidget(mEngineComboBox);

    mConfigureEngine->setObjectName(QStringLiteral("mConfigureEngine"));
    mainLayout->addWidget(mConfigureEngine);
    mConfigureEngine->setEnabled(false); // Disable by default
    mConfigureEngine->setIcon(QIcon::fromTheme(QStringLiteral("settings-configure")));
    connect(mConfigureEngine, &QToolButton::clicked, this, &TextAutoGenerateTextConfigureComboWidget::slotConfigureEngine);
    connect(mEngineComboBox, &QComboBox::currentIndexChanged, this, &TextAutoGenerateTextConfigureComboWidget::slotEngineChanged);

    fillEngine();
}

TextAutoGenerateTextConfigureComboWidget::~TextAutoGenerateTextConfigureComboWidget() = default;

void TextAutoGenerateTextConfigureComboWidget::slotConfigureEngine()
{
    const QString engine = mEngineComboBox->currentData().toString();
    if (TextAutoGenerateText::TextAutoGenerateEngineLoader::self()->hasConfigurationDialog(engine)) {
        if (TextAutoGenerateText::TextAutoGenerateEngineLoader::self()->showConfigureDialog(engine, this)) {
            Q_EMIT configureChanged(engine);
        }
    }
}

void TextAutoGenerateTextConfigureComboWidget::fillEngine()
{
    mEngineComboBox->clear();
    TextAutoGenerateText::TextAutoGenerateEngineLoader::self()->loadPlugins();
    const QMap<QString, QString> map = TextAutoGenerateText::TextAutoGenerateEngineLoader::self()->textAutoGenerateTextEngineInfos();
    QMapIterator<QString, QString> iMap(map);
    while (iMap.hasNext()) {
        iMap.next();
        mEngineComboBox->addItem(iMap.value(), iMap.key());
    }
}

void TextAutoGenerateTextConfigureComboWidget::slotEngineChanged(int index)
{
    const QString engine = mEngineComboBox->itemData(index).toString();
    mConfigureEngine->setEnabled(TextAutoGenerateText::TextAutoGenerateEngineLoader::self()->hasConfigurationDialog(engine));
    Q_EMIT engineChanged(engine);
}

void TextAutoGenerateTextConfigureComboWidget::load()
{
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TextAutoGenerateEngineUtil::groupAutoGenerateTextName());
    const QString engine = groupTranslate.readEntry(TextAutoGenerateEngineUtil::engineTranslateName(), TextAutoGenerateEngineUtil::defaultEngineName());
    const int index = mEngineComboBox->findData(engine);
    if (index != -1) {
        mEngineComboBox->setCurrentIndex(index);
    }
}

void TextAutoGenerateTextConfigureComboWidget::save()
{
    const QString engine = mEngineComboBox->currentData().toString();
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TextAutoGenerateEngineUtil::groupAutoGenerateTextName());
    groupTranslate.writeEntry(TextAutoGenerateEngineUtil::engineTranslateName(), engine);
    KSharedConfig::openConfig()->sync();
}

#include "moc_textautogeneratetextconfigurecombowidget.cpp"
