/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddinstancewidget.h"
#include "textautogeneratetextinstancecombobox.h"
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateAddInstanceWidget::TextAutoGenerateAddInstanceWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mInstanceComboBox(new TextAutoGenerateTextInstanceComboBox(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18n("Select a Type of Instance:"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mInstanceComboBox->setObjectName(QStringLiteral("mInstanceComboBox"));
    mainLayout->addWidget(mInstanceComboBox);
}

TextAutoGenerateAddInstanceWidget::~TextAutoGenerateAddInstanceWidget() = default;

TextAutoGenerateTextClient::SupportedServer TextAutoGenerateAddInstanceWidget::selectedInstanceType() const
{
    return mInstanceComboBox->selectedInstanceType();
}

#include "moc_textautogenerateaddinstancewidget.cpp"
