/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfigurecustomizewidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
// https://docs.ollama.com/gpu#overrides-on-linux
OllamaConfigureCustomizeWidget::OllamaConfigureCustomizeWidget(QWidget *parent)
    : QWidget{parent}
    , mVulkanSupportLineEdit(new QLineEdit(this))
    , mCudaVisibleDeviceLineEdit(new QLineEdit(this))
    , mRocrVisibleDeviceLineEdit(new QLineEdit(this))
    , mOverrideGfxVersionLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mVulkanSupportLineEdit->setObjectName(u"mVulkanSupportLineEdit"_s);
    mainLayout->addRow(i18n("Vulkan GPU Support:"), mVulkanSupportLineEdit);

    mCudaVisibleDeviceLineEdit->setObjectName(u"mCudaVisibleDeviceLineEdit"_s);
    mainLayout->addRow(i18n("NVIDIA GPU Selection:"), mCudaVisibleDeviceLineEdit);

    mRocrVisibleDeviceLineEdit->setObjectName(u"mRocrVisibleDeviceLineEdit"_s);
    mainLayout->addRow(i18n("AMD GPU Selection:"), mRocrVisibleDeviceLineEdit);

    mOverrideGfxVersionLineEdit->setObjectName(u"mOverrideGfxVersionLineEdit"_s);
    mainLayout->addRow(i18n("Override GFX version:"), mOverrideGfxVersionLineEdit);
}

OllamaConfigureCustomizeWidget::~OllamaConfigureCustomizeWidget() = default;

void OllamaConfigureCustomizeWidget::setCustomizeInfo(const CustomizeInfo &info)
{
    // TODO
}

OllamaConfigureCustomizeWidget::CustomizeInfo OllamaConfigureCustomizeWidget::customizeInfo() const
{
    const OllamaConfigureCustomizeWidget::CustomizeInfo info{
        .vulkanSupport = mVulkanSupportLineEdit->text(),
        .cudaVisibleDevice = mCudaVisibleDeviceLineEdit->text(),
        .rocrVisibleDevice = mRocrVisibleDeviceLineEdit->text(),
        .overrideGfxVersion = mOverrideGfxVersionLineEdit->text(),
    };
    return info;
}

#include "moc_ollamaconfigurecustomizewidget.cpp"
