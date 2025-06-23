/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "bergamotenginesettingswidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <thread>

BergamotEngineSettingsWidget::BergamotEngineSettingsWidget(QWidget *parent)
    : QWidget{parent}
    , mNumberThreads(new QComboBox(this))
    , mMemoryByThreads(new QComboBox(this))
    , mUseLocalCache(new QCheckBox(i18nc("@option:check", "Use translation cache"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto resourceBox = new QGroupBox(i18n("Resource Usage"), this);
    resourceBox->setObjectName(u"resourceBox"_s);
    mainLayout->addWidget(resourceBox);

    mNumberThreads->setObjectName(u"mNumberThreads"_s);
    mMemoryByThreads->setObjectName(u"mMemoryByThreads"_s);

    mUseLocalCache->setObjectName(u"mUseLocalCache"_s);

    auto formLayout = new QFormLayout;
    formLayout->setObjectName(u"formLayout"_s);
    resourceBox->setLayout(formLayout);
    formLayout->addRow(i18n("Thread:"), mNumberThreads);
    formLayout->addRow(i18n("Memory by Thread:"), mMemoryByThreads);
    formLayout->addWidget(mUseLocalCache);
    fillCombobox();
}

BergamotEngineSettingsWidget::~BergamotEngineSettingsWidget() = default;

void BergamotEngineSettingsWidget::setSettingsInfo(const BergamotEngineUtils::SettingsInfo &info)
{
    mNumberThreads->setCurrentIndex(mNumberThreads->findData(info.numberOfThread));
    mMemoryByThreads->setCurrentIndex(mMemoryByThreads->findData(info.memoryByThread));
    mUseLocalCache->setChecked(info.useLocalCache);
}

BergamotEngineUtils::SettingsInfo BergamotEngineSettingsWidget::settingsInfo() const
{
    BergamotEngineUtils::SettingsInfo info;
    info.memoryByThread = mMemoryByThreads->currentData().toInt();
    info.numberOfThread = mNumberThreads->currentData().toInt();
    info.useLocalCache = mUseLocalCache->isChecked();
    return info;
}

void BergamotEngineSettingsWidget::fillCombobox()
{
    const auto processorCount = std::thread::hardware_concurrency();

    for (int cores = processorCount; cores > 0; cores -= 2) {
        mNumberThreads->addItem(QString::number(cores), cores);
    }

    const QList<int> memorys = {64, 128, 256, 512, 768, 1024, 1280, 1536, 1762, 2048};
    for (const int memory : memorys) {
        mMemoryByThreads->addItem(QString::number(memory), memory);
    }
}

#include "moc_bergamotenginesettingswidget.cpp"
