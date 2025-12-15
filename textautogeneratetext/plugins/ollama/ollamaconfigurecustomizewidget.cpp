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
OllamaConfigureCustomizeWidget::OllamaConfigureCustomizeWidget(QWidget *parent)
    : QWidget{parent}
    , mVulkanSupport(new QCheckBox(i18n("Vulkan"), this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
}

OllamaConfigureCustomizeWidget::~OllamaConfigureCustomizeWidget() = default;

#include "moc_ollamaconfigurecustomizewidget.cpp"
