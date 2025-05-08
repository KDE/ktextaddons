/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateconfigurewidget.h"
#include "textautogeneratetextconfigurecombowidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateConfigureWidget::TextAutoGenerateConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mPluginComboBox(new TextAutoGenerateTextConfigureComboWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto hbox = new QHBoxLayout;
    hbox->setObjectName(QStringLiteral("hbox"));
    hbox->setContentsMargins({});
    mainLayout->addLayout(hbox);

    auto label = new QLabel(i18n("Engine:"), this);
    label->setObjectName(QStringLiteral("label"));
    label->setTextFormat(Qt::PlainText);
    hbox->addWidget(label);

    mPluginComboBox->setObjectName(QStringLiteral("mPluginComboBox"));
    hbox->addWidget(mPluginComboBox);
}

TextAutoGenerateConfigureWidget::~TextAutoGenerateConfigureWidget() = default;

void TextAutoGenerateConfigureWidget::saveSettings()
{
    mPluginComboBox->save();
}

void TextAutoGenerateConfigureWidget::loadSettings()
{
    mPluginComboBox->load();
}

#include "moc_textautogenerateconfigurewidget.cpp"
