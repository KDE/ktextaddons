/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonoptionswidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

OllamaCommonOptionsWidget::OllamaCommonOptionsWidget(QWidget *parent)
    : QWidget{parent}
    , mExpose(new QCheckBox(i18n("Expose Ollama to Network"), this))
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
    mExpose->setToolTip(i18nc("@info:tooltip", "Make Ollama available for other devices and software in local network."));
    groupCustomizeGroupboxLayout->addRow(i18n("Expose Ollama to Network"), mExpose);
}

OllamaCommonOptionsWidget::~OllamaCommonOptionsWidget() = default;

#include "moc_ollamacommonoptionswidget.cpp"
