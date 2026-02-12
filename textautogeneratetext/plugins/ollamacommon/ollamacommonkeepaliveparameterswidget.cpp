/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonkeepaliveparameterswidget.h"
#include "ollamacommonkeepaliveparameterscombobox.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
OllamaCommonKeepAliveParametersWidget::OllamaCommonKeepAliveParametersWidget(QWidget *parent)
    : QWidget{parent}
    , mOllamaCommonKeepAliveParametersComboBox(new OllamaCommonKeepAliveParametersComboBox(this))
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
}

OllamaCommonKeepAliveParametersWidget::~OllamaCommonKeepAliveParametersWidget() = default;

#include "moc_ollamacommonkeepaliveparameterswidget.cpp"
