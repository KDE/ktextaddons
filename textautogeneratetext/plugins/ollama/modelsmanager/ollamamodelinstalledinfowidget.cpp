/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfowidget.h"
#include "autogeneratetext_ollama_debug.h"
#include "ollamanetworkurlbutton.h"
#include "widgets/common/textautogenerateflowlayout.h"
#include <KLocalizedString>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
OllamaModelInstalledInfoWidget::OllamaModelInstalledInfoWidget(QWidget *parent)
    : QWidget{parent}
    , mFamilyNameLabel(new QLabel(this))
    , mParameterSizeLabel(new QLabel(this))
    , mQuantizationLevelLabel(new QLabel(this))
    , mModifiedAtLabel(new QLabel(this))
    , mMainLayout(new QVBoxLayout(this))
    , mNetworkUrlButton(new OllamaNetworkUrlButton(this))
{
    mMainLayout->setObjectName(u"mMainLayout"_s);

    mNetworkUrlButton->setObjectName(u"mNetworkUrlButton");
    mMainLayout->addWidget(mNetworkUrlButton, 0, Qt::AlignTop);
    {
        auto label = new QLabel(i18n("Family:"), this);
        mMainLayout->addWidget(label, 0, Qt::AlignTop);
        changeFont(label);

        mFamilyNameLabel->setObjectName(u"mFamilyNameLabel"_s);
        mMainLayout->addWidget(mFamilyNameLabel, 0, Qt::AlignTop);
    }

    {
        auto label = new QLabel(i18n("Parameter Size:"), this);
        mMainLayout->addWidget(label, 0, Qt::AlignTop);
        changeFont(label);

        mParameterSizeLabel->setObjectName(u"mParameterSizeLabel"_s);
        mMainLayout->addWidget(mParameterSizeLabel, 0, Qt::AlignTop);
    }

    {
        auto label = new QLabel(i18n("Quantization Level:"), this);
        mMainLayout->addWidget(label, 0, Qt::AlignTop);
        changeFont(label);

        mQuantizationLevelLabel->setObjectName(u"mQuantizationLevelLabel"_s);
        mMainLayout->addWidget(mQuantizationLevelLabel, 0, Qt::AlignTop);
    }

    {
        auto label = new QLabel(i18n("Modified At:"), this);
        mMainLayout->addWidget(label, 0, Qt::AlignTop);
        changeFont(label);

        mModifiedAtLabel->setObjectName(u"mModifiedAtLabel"_s);
        mMainLayout->addWidget(mModifiedAtLabel, 0, Qt::AlignTop);
    }
}

OllamaModelInstalledInfoWidget::~OllamaModelInstalledInfoWidget() = default;

void OllamaModelInstalledInfoWidget::changeFont(QLabel *label)
{
    QFont f = label->font();
    f.setBold(true);
    label->setFont(f);
}

void OllamaModelInstalledInfoWidget::setOllamaModelInstalledInfo(const OllamaModelInstalledInfo &info)
{
    mNetworkUrlButton->setModelUrl(info.modelUrl());
    mFamilyNameLabel->setText(info.family());
    mParameterSizeLabel->setText(info.parameterSize());
    mQuantizationLevelLabel->setText(info.quantizationLevel());
    mModifiedAtLabel->setText(info.modifyAtInLocal());
    if (mInfoWidget) {
        mMainLayout->removeWidget(mInfoWidget);
        mInfoWidget->deleteLater();
    }
    mInfoWidget = new QWidget(this);
    mMainLayout->addWidget(mInfoWidget, 1);
    auto infoLayout = new QVBoxLayout(mInfoWidget);
    infoLayout->setContentsMargins({});

    if (const QString parentModelName = info.parentModel(); !parentModelName.isEmpty()) {
        auto label = new QLabel(i18n("Parent Model:"), mInfoWidget);
        infoLayout->addWidget(label);
        changeFont(label);

        auto parentModelLabel = new QLabel(parentModelName, mInfoWidget);
        infoLayout->addWidget(parentModelLabel);
    }

    auto languagesGroupBox = new QGroupBox(i18n("Languages Supported"), mInfoWidget);
    infoLayout->addWidget(languagesGroupBox);
    auto vboxLanguagesLayout = new TextAutoGenerateText::TextAutoGenerateFlowLayout(languagesGroupBox);
    for (const auto &lang : info.languages()) {
        const QLocale locale(lang);
        if (locale.language() == QLocale::Language::C) {
            qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << " impossible to convert to language " << lang;
            continue;
        }
        vboxLanguagesLayout->addWidget(new QLabel(locale.nativeLanguageName(), mInfoWidget));
    }
    QStringList categoriesName;
    const TextAutoGenerateText::TextAutoGenerateManager::Categories categories = info.categories();
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Tools, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Multilingual, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Code, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Math, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Vision, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Embedding, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Reasoning, categories);
    if (!categoriesName.isEmpty()) {
        auto featuresGroupBox = new QGroupBox(i18n("Features Supported"), mInfoWidget);
        infoLayout->addWidget(featuresGroupBox);
        auto vboxfeaturesLayout = new TextAutoGenerateText::TextAutoGenerateFlowLayout(featuresGroupBox);
        for (const QString &name : std::as_const(categoriesName)) {
            vboxfeaturesLayout->addWidget(new QLabel(name, mInfoWidget));
        }
    }

    infoLayout->addStretch(1);
}

void OllamaModelInstalledInfoWidget::appendCategories(QStringList &lst,
                                                      TextAutoGenerateText::TextAutoGenerateManager::Category cat,
                                                      TextAutoGenerateText::TextAutoGenerateManager::Categories categories)
{
    if (categories & cat) {
        lst.append(TextAutoGenerateText::TextAutoGenerateManager::convertCategoryToI18n(cat));
    }
}

#include "moc_ollamamodelinstalledinfowidget.cpp"
