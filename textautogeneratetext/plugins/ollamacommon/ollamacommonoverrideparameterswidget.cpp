/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonoverrideparameterswidget.h"
#include <KLocalizedString>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
OllamaCommonOverrideParametersWidget::OllamaCommonOverrideParametersWidget(QWidget *parent)
    : QWidget{parent}
    , mTemperature(new QDoubleSpinBox(this))
    , mSeed(new QSpinBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});

    auto groupCustomizeGroupbox = new QGroupBox(i18n("Override Parameters"), this);
    groupCustomizeGroupbox->setObjectName(u"groupCustomizeGroupbox"_s);
    mainLayout->addWidget(groupCustomizeGroupbox);

    auto groupCustomizeGroupboxLayout = new QVBoxLayout(groupCustomizeGroupbox);
    groupCustomizeGroupboxLayout->setObjectName(u"groupCustomizeGroupboxLayout"_s);

    mainLayout->addWidget(groupCustomizeGroupbox);

    mTemperature->setObjectName(u"mTemperature"_s);
    auto label = new QLabel(i18n("Temperature:"), this);
    groupCustomizeGroupboxLayout->addWidget(label);
    groupCustomizeGroupboxLayout->addWidget(mTemperature);
    mTemperature->setRange(0.0, 10.0);
    mTemperature->setSingleStep(0.01);
    mTemperature->setToolTip(i18nc("@info:tooltip", "The temperature of the model. Increasing the temperature will make the model answer more creatively."));

    mSeed->setObjectName(u"mSeed"_s);
    label = new QLabel(i18n("Seed:"), this);
    groupCustomizeGroupboxLayout->addWidget(label);
    groupCustomizeGroupboxLayout->addWidget(mSeed);

    mSeed->setToolTip(i18nc("@info:tooltip",
                            "Sets the random number seed to use for generation. Setting this to a specific number will make the model generate the same text "
                            "for the same prompt. (Default: 0)"));
    mSeed->setRange(0, 10);
    mSeed->setSingleStep(1);
}

OllamaCommonOverrideParametersWidget::~OllamaCommonOverrideParametersWidget() = default;

#include "moc_ollamacommonoverrideparameterswidget.cpp"
