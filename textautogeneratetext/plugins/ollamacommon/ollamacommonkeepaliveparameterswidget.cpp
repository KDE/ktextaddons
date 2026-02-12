/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonkeepaliveparameterswidget.h"
#include "ollamacommonkeepaliveparameterscombobox.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
OllamaCommonKeepAliveParametersWidget::OllamaCommonKeepAliveParametersWidget(QWidget *parent)
    : QWidget{parent}
    , mOllamaCommonKeepAliveParametersComboBox(new OllamaCommonKeepAliveParametersComboBox(this))
    , mKeepAliveMinutes(new QSpinBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});

    auto groupCustomizeGroupbox = new QGroupBox(i18n("Keep Alive"), this);
    groupCustomizeGroupbox->setObjectName(u"groupCustomizeGroupbox"_s);
    mainLayout->addWidget(groupCustomizeGroupbox);

    auto groupCustomizeGroupboxLayout = new QFormLayout(groupCustomizeGroupbox);
    groupCustomizeGroupboxLayout->setObjectName(u"groupCustomizeGroupboxLayout"_s);
    mainLayout->addWidget(groupCustomizeGroupbox);

    mOllamaCommonKeepAliveParametersComboBox->setObjectName(u"mOllamaCommonKeepAliveParametersComboBox"_s);
    mOllamaCommonKeepAliveParametersComboBox->setToolTip(i18nc("@info:tooltip", "How the instance should handle idle models"));
    mKeepAliveMinutes->setObjectName(u"mKeepAliveMinutes"_s);
    mKeepAliveMinutes->setMinimum(1);
    mKeepAliveMinutes->setToolTip(i18nc("@info:tooltip", "The amount of time the instance should keep models loaded after they go idle."));

    groupCustomizeGroupboxLayout->addRow(i18n("Presets"), mOllamaCommonKeepAliveParametersComboBox);
    groupCustomizeGroupboxLayout->addRow(i18n("Minutes"), mKeepAliveMinutes);
}

OllamaCommonKeepAliveParametersWidget::~OllamaCommonKeepAliveParametersWidget() = default;

OllamaCommonKeepAliveParametersWidget::KeepAliveInfo OllamaCommonKeepAliveParametersWidget::keepAliveInfo() const
{
    const OllamaCommonKeepAliveParametersWidget::KeepAliveInfo info{
        .keepAliveType = mOllamaCommonKeepAliveParametersComboBox->keepAliveType(),
        .minutes = mKeepAliveMinutes->value(),
    };
    return info;
}

void OllamaCommonKeepAliveParametersWidget::setKeepAliveInfo(const KeepAliveInfo &info)
{
    mKeepAliveMinutes->setValue(info.minutes);
    mOllamaCommonKeepAliveParametersComboBox->setKeepAliveType(info.keepAliveType);
    // TODO
}

#include "moc_ollamacommonkeepaliveparameterswidget.cpp"
