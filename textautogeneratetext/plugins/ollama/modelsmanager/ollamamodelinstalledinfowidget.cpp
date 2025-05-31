/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfowidget.h"
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
    mMainLayout->setObjectName(QStringLiteral("mainLayout"));

    {
        auto label = new QLabel(i18n("Family:"), this);
        mMainLayout->addWidget(label);
        changeFont(label);

        mFamilyNameLabel->setObjectName(QStringLiteral("mFamilyNameLabel"));
        mMainLayout->addWidget(mFamilyNameLabel);
    }

    {
        auto label = new QLabel(i18n("Parameter Size:"), this);
        mMainLayout->addWidget(label);
        changeFont(label);

        mParameterSizeLabel->setObjectName(QStringLiteral("mParameterSizeLabel"));
        mMainLayout->addWidget(mParameterSizeLabel);
    }

    {
        auto label = new QLabel(i18n("Quantization Level:"), this);
        mMainLayout->addWidget(label);
        changeFont(label);

        mQuantizationLevelLabel->setObjectName(QStringLiteral("mQuantizationLevelLabel"));
        mMainLayout->addWidget(mQuantizationLevelLabel);
    }

    {
        auto label = new QLabel(i18n("Modified At:"), this);
        mMainLayout->addWidget(label);
        changeFont(label);

        mModifiedAtLabel->setObjectName(QStringLiteral("mModifiedAtLabel"));
        mMainLayout->addWidget(mModifiedAtLabel);
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

    QString installedName = info.model();
    const int position = installedName.indexOf(QLatin1Char(':'));
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
        auto featuresGroupBox = new QGroupBox(i18n("Features Supported"), mInfoWidget);
        infoLayout->addWidget(featuresGroupBox);
        auto vboxfeaturesLayout = new OllamaModelFlowLayout(featuresGroupBox);
        for (const auto &cat : (*it).categoriesName()) {
            vboxfeaturesLayout->addWidget(new QLabel(cat, mInfoWidget));
        }
    }

    infoLayout->addStretch(1);
}

#include "moc_ollamamodelinstalledinfowidget.cpp"
