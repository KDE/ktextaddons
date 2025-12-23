/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfigurecustomizewidget.h"
#include <KLineEdit>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KUrlRequester>
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
    , mDefaultModelPath(new KUrlRequester(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mVulkanSupportLineEdit->setObjectName(u"mVulkanSupportLineEdit"_s);
    mVulkanSupportLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Vulkan GPU Support:"), mVulkanSupportLineEdit);
    KLineEditEventHandler::catchReturnKey(mVulkanSupportLineEdit);

    mCudaVisibleDeviceLineEdit->setObjectName(u"mCudaVisibleDeviceLineEdit"_s);
    mCudaVisibleDeviceLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("NVIDIA GPU Selection:"), mCudaVisibleDeviceLineEdit);
    KLineEditEventHandler::catchReturnKey(mCudaVisibleDeviceLineEdit);

    mRocrVisibleDeviceLineEdit->setObjectName(u"mRocrVisibleDeviceLineEdit"_s);
    mRocrVisibleDeviceLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("AMD GPU Selection:"), mRocrVisibleDeviceLineEdit);
    KLineEditEventHandler::catchReturnKey(mRocrVisibleDeviceLineEdit);

    mOverrideGfxVersionLineEdit->setObjectName(u"mOverrideGfxVersionLineEdit"_s);
    mOverrideGfxVersionLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Override GFX version:"), mOverrideGfxVersionLineEdit);
    KLineEditEventHandler::catchReturnKey(mOverrideGfxVersionLineEdit);

    mDefaultModelPath->setObjectName(u"mDefaultModelPath"_s);
    mainLayout->addRow(i18n("Default Model Path:"), mDefaultModelPath);
    KLineEditEventHandler::catchReturnKey(mDefaultModelPath->lineEdit());
    mDefaultModelPath->setMode(KFile::Directory | KFile::LocalOnly);
}

OllamaConfigureCustomizeWidget::~OllamaConfigureCustomizeWidget() = default;

void OllamaConfigureCustomizeWidget::setCustomizeInfo(const CustomizeInfo &info)
{
    mVulkanSupportLineEdit->setText(info.vulkanSupport);
    mCudaVisibleDeviceLineEdit->setText(info.cudaVisibleDevice);
    mRocrVisibleDeviceLineEdit->setText(info.rocrVisibleDevice);
    mOverrideGfxVersionLineEdit->setText(info.overrideGfxVersion);
    mDefaultModelPath->setText(info.defaultModelPath);
}

OllamaConfigureCustomizeWidget::CustomizeInfo OllamaConfigureCustomizeWidget::customizeInfo() const
{
    const OllamaConfigureCustomizeWidget::CustomizeInfo info{
        .vulkanSupport = mVulkanSupportLineEdit->text(),
        .cudaVisibleDevice = mCudaVisibleDeviceLineEdit->text(),
        .rocrVisibleDevice = mRocrVisibleDeviceLineEdit->text(),
        .overrideGfxVersion = mOverrideGfxVersionLineEdit->text(),
        .defaultModelPath = mDefaultModelPath->lineEdit()->text(),
    };
    return info;
}

#include "moc_ollamaconfigurecustomizewidget.cpp"
