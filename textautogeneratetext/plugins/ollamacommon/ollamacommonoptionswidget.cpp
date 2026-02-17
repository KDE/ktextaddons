/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonoptionswidget.h"
#include "ollamacommonsharenamecombobox.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

OllamaCommonOptionsWidget::OllamaCommonOptionsWidget(ExtraOptions options, QWidget *parent)
    : QWidget{parent}
    , mExpose(new QCheckBox(i18n("Expose Ollama to Network"), this))
    , mThoughtProcessing(new QCheckBox(i18n("Thought Processing"), this))
    , mExtraOptions(options)
    , mOllamaCommonShareNameComboBox(new OllamaCommonShareNameComboBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});

    auto groupCustomizeGroupbox = new QGroupBox(i18n("Options"), this);
    groupCustomizeGroupbox->setObjectName(u"groupCustomizeGroupbox"_s);
    mainLayout->addWidget(groupCustomizeGroupbox);

    auto groupCustomizeGroupboxLayout = new QFormLayout(groupCustomizeGroupbox);
    groupCustomizeGroupboxLayout->setObjectName(u"groupCustomizeGroupboxLayout"_s);

    mExpose->setObjectName(u"mExpose"_s);
    mExpose->setVisible(false);
    mExpose->setToolTip(i18nc("@info:tooltip", "Make Ollama available for other devices and software in local network."));
    groupCustomizeGroupboxLayout->addWidget(mExpose);
    if (options & OllamaCommonOptionsWidget::ExtraOption::ExposeToNetwork) {
        mExpose->setVisible(true);
    }

    mThoughtProcessing->setObjectName(u"mThoughtProcessing"_s);
    mThoughtProcessing->setToolTip(i18nc("@info:tooltip", "Have compatible reasoning models think about their response before generating a message."));
    groupCustomizeGroupboxLayout->addWidget(mThoughtProcessing);

    mOllamaCommonShareNameComboBox->setObjectName(u"mOllamaCommonShareNameComboBox"_s);
    groupCustomizeGroupboxLayout->addRow(i18n("Share Name:"), mOllamaCommonShareNameComboBox);
}

OllamaCommonOptionsWidget::~OllamaCommonOptionsWidget() = default;

OllamaCommonOptionsWidget::OllamaCommonOptionsInfo OllamaCommonOptionsWidget::optionsInfo() const
{
    const OllamaCommonOptionsWidget::OllamaCommonOptionsInfo info{
        .exposeToNetwork = mExpose->isChecked(),
        .thoughtProcessing = mThoughtProcessing->isChecked(),
        .shareNameType = mOllamaCommonShareNameComboBox->shareNameType(),
    };
    return info;
}

void OllamaCommonOptionsWidget::setOptionsInfo(const OllamaCommonOptionsInfo &info)
{
    mExpose->setChecked(info.exposeToNetwork);
    mThoughtProcessing->setChecked(info.thoughtProcessing);
    mOllamaCommonShareNameComboBox->setShareNameType(info.shareNameType);
}

#include "moc_ollamacommonoptionswidget.cpp"
