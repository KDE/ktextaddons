/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonoverrideparameterswidget.h"
#include <KLocalizedString>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>

using namespace Qt::Literals::StringLiterals;
OllamaCommonOverrideParametersWidget::OllamaCommonOverrideParametersWidget(QWidget *parent)
    : QWidget{parent}
    , mTemperature(new QDoubleSpinBox(this))
    , mSeed(new QSpinBox(this))
    , mContextWindowSize(new QSpinBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});

    auto groupCustomizeGroupbox = new QGroupBox(i18n("Override Parameters"), this);
    groupCustomizeGroupbox->setObjectName(u"groupCustomizeGroupbox"_s);
    mainLayout->addWidget(groupCustomizeGroupbox);

    auto groupCustomizeGroupboxLayout = new QFormLayout(groupCustomizeGroupbox);
    groupCustomizeGroupboxLayout->setObjectName(u"groupCustomizeGroupboxLayout"_s);

    mainLayout->addWidget(groupCustomizeGroupbox);

    mTemperature->setObjectName(u"mTemperature"_s);
    mTemperature->setRange(0.0, 10.0);
    mTemperature->setSingleStep(0.01);
    mTemperature->setToolTip(i18nc("@info:tooltip", "The temperature of the model. Increasing the temperature will make the model answer more creatively."));
    groupCustomizeGroupboxLayout->addRow(i18n("Temperature:"), mTemperature);

    mSeed->setObjectName(u"mSeed"_s);
    mSeed->setToolTip(i18nc("@info:tooltip",
                            "Sets the random number seed to use for generation. Setting this to a specific number will make the model generate the same text "
                            "for the same prompt. (Default: 0)"));
    mSeed->setRange(0, 10);
    mSeed->setSingleStep(1);

    mContextWindowSize->setObjectName(u"mContextWindowSize"_s);
    mContextWindowSize->setToolTip(i18nc("@info:tooltip", "Controls how many token (piece of text) the model can process and remember at once."));
    mContextWindowSize->setRange(1, 999999);
    mContextWindowSize->setSingleStep(1);
    groupCustomizeGroupboxLayout->addRow(i18n("Context Window Size:"), mContextWindowSize);
}

OllamaCommonOverrideParametersWidget::~OllamaCommonOverrideParametersWidget() = default;

void OllamaCommonOverrideParametersWidget::setParametersInfo(const OverrideParametersInfo &info)
{
    mTemperature->setValue(info.temperature);
    mSeed->setValue(info.seed);
}

OllamaCommonOverrideParametersWidget::OverrideParametersInfo OllamaCommonOverrideParametersWidget::parametersInfo() const
{
    const OllamaCommonOverrideParametersWidget::OverrideParametersInfo info{
        .temperature = mTemperature->value(),
        .seed = mSeed->value(),
    };
    return info;
}

#include "moc_ollamacommonoverrideparameterswidget.cpp"
