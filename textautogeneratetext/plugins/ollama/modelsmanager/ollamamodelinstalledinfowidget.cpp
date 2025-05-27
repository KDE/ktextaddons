/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfowidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>

OllamaModelInstalledInfoWidget::OllamaModelInstalledInfoWidget(QWidget *parent)
    : QWidget{parent}
    , mFamilyNameLabel(new QLabel(this))
    , mParameterSizeLabel(new QLabel(this))
    , mQuantizationLevelLabel(new QLabel(this))
    , mModifiedAtLabel(new QLabel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    {
        auto label = new QLabel(i18n("Family:"), this);
        mainLayout->addWidget(label);
        changeFont(label);

        mFamilyNameLabel->setObjectName(QStringLiteral("mFamilyNameLabel"));
        mainLayout->addWidget(mFamilyNameLabel);
    }

    {
        auto label = new QLabel(i18n("Parameter Size:"), this);
        mainLayout->addWidget(label);
        changeFont(label);

        mParameterSizeLabel->setObjectName(QStringLiteral("mParameterSizeLabel"));
        mainLayout->addWidget(mParameterSizeLabel);
    }

    {
        auto label = new QLabel(i18n("Quantization Level:"), this);
        mainLayout->addWidget(label);
        changeFont(label);

        mQuantizationLevelLabel->setObjectName(QStringLiteral("mQuantizationLevelLabel"));
        mainLayout->addWidget(mQuantizationLevelLabel);
    }

    {
        auto label = new QLabel(i18n("Modified At:"), this);
        mainLayout->addWidget(label);
        changeFont(label);

        mModifiedAtLabel->setObjectName(QStringLiteral("mModifiedAtLabel"));
        mainLayout->addWidget(mModifiedAtLabel);
    }
    mainLayout->addStretch(1);
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
    mFamilyNameLabel->setText(info.family());
    mParameterSizeLabel->setText(info.parameterSize());
    mQuantizationLevelLabel->setText(info.quantizationLevel());
    mModifiedAtLabel->setText(info.modifyAt());
}

#include "moc_ollamamodelinstalledinfowidget.cpp"
