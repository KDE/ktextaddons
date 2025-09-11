/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolpluginconfigurewidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateToolPluginConfigureWidget::TextAutoGenerateToolPluginConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mDescriptionLabel(new QLabel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18nc("@label:textbox", "Description:"), this);
    mainLayout->addWidget(label);

    mDescriptionLabel->setObjectName("mDescriptionLabel"_L1);
    mainLayout->addWidget(mDescriptionLabel);
}

TextAutoGenerateToolPluginConfigureWidget::~TextAutoGenerateToolPluginConfigureWidget() = default;

void TextAutoGenerateToolPluginConfigureWidget::initialize(TextAutoGenerateTextToolPlugin *plugin)
{
    if (plugin) {
        mDescriptionLabel->setText(plugin->descriptions());
    }
}

#include "moc_textautogeneratetoolpluginconfigurewidget.cpp"
