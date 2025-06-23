/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfowidget.h"
using namespace Qt::Literals::StringLiterals;

#include "ollamamodelflowlayout.h"
#include <KLocalizedString>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

OllamaModelInstalledInfoWidget::OllamaModelInstalledInfoWidget(QWidget *parent)
    : QWidget{parent}
    , mFamilyNameLabel(new QLabel(this))
    , mParameterSizeLabel(new QLabel(this))
    , mQuantizationLevelLabel(new QLabel(this))
    , mModifiedAtLabel(new QLabel(this))
    , mMainLayout(new QVBoxLayout(this))
{
    mMainLayout->setObjectName(u"mainLayout"_s);

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

void OllamaModelInstalledInfoWidget::setOllamaModelInstalledInfo(const OllamaModelInstalledInfo &info,
                                                                 const QList<OllamaModelAvailableInfo> &infoAvailableInfos)
{
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

    QString installedName = info.model();
    const int position = installedName.indexOf(u':');
    installedName = installedName.first(position);
    auto matchesModelName = [&](const OllamaModelAvailableInfo &availableInfo) {
        return availableInfo.name() == installedName;
    };
    auto it = std::find_if(infoAvailableInfos.begin(), infoAvailableInfos.end(), matchesModelName);
    if (it != infoAvailableInfos.end()) {
        auto languagesGroupBox = new QGroupBox(i18n("Languages Supported"), mInfoWidget);
        infoLayout->addWidget(languagesGroupBox);
        auto vboxLanguagesLayout = new OllamaModelFlowLayout(languagesGroupBox);
        for (const auto &lang : (*it).languages()) {
            const QLocale locale(lang);
            vboxLanguagesLayout->addWidget(new QLabel(QLocale::languageToString(locale.language()), mInfoWidget));
        }

        QStringList categoriesName;
        const OllamaModelAvailableInfo::Categories categories = (*it).categories();
        appendCategories(categoriesName, OllamaModelAvailableInfo::Category::Tools, categories);
        appendCategories(categoriesName, OllamaModelAvailableInfo::Category::Multilingual, categories);
        appendCategories(categoriesName, OllamaModelAvailableInfo::Category::Code, categories);
        appendCategories(categoriesName, OllamaModelAvailableInfo::Category::Math, categories);
        appendCategories(categoriesName, OllamaModelAvailableInfo::Category::Vision, categories);
        appendCategories(categoriesName, OllamaModelAvailableInfo::Category::Embedding, categories);
        appendCategories(categoriesName, OllamaModelAvailableInfo::Category::Reasoning, categories);
        if (!categoriesName.isEmpty()) {
            auto featuresGroupBox = new QGroupBox(i18n("Features Supported"), mInfoWidget);
            infoLayout->addWidget(featuresGroupBox);
            auto vboxfeaturesLayout = new OllamaModelFlowLayout(featuresGroupBox);
            for (const QString &name : categoriesName) {
                vboxfeaturesLayout->addWidget(new QLabel(name, mInfoWidget));
            }
        }
    }

    infoLayout->addStretch(1);
}

void OllamaModelInstalledInfoWidget::appendCategories(QStringList &lst, OllamaModelAvailableInfo::Category cat, OllamaModelAvailableInfo::Categories categories)
{
    if (categories & cat) {
        lst.append(OllamaModelAvailableInfo::convertCategoryToI18n(cat));
    }
}

#include "moc_ollamamodelinstalledinfowidget.cpp"
