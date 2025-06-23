/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatewidget.h"
using namespace Qt::Literals::StringLiterals;

#include "ollamamodelcreatefromexistingmodelwidget.h"
#include <KLocalizedString>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

OllamaModelCreateWidget::OllamaModelCreateWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mManager(manager)
    , mStackWidget(new QStackedWidget(this))
    , mOllamaModelCreateFromExistingModelWidget(new OllamaModelCreateFromExistingModelWidget(manager, this))
    , mSelectModeWidget(new QWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});

    mStackWidget->setObjectName(u"mStackWidget"_s);
    mainLayout->addWidget(mStackWidget);

    mOllamaModelCreateFromExistingModelWidget->setObjectName(u"mOllamaModelCreateFromExistingModelWidget"_s);
    mSelectModeWidget->setObjectName(u"mSelectModeWidget"_s);

    auto selectModeWidgetLayout = new QHBoxLayout(mSelectModeWidget);

    mStackWidget->addWidget(mOllamaModelCreateFromExistingModelWidget);
    mStackWidget->addWidget(mSelectModeWidget);

    mStackWidget->setCurrentWidget(mSelectModeWidget);

    auto importModelFromGGUFFileButton = new QPushButton(i18nc("@action:button", "Load GGUF File…"), this);
    importModelFromGGUFFileButton->setObjectName(u"importModelFromGGUFFileButton"_s);
    selectModeWidgetLayout->addWidget(importModelFromGGUFFileButton, 0, Qt::AlignTop);
    connect(importModelFromGGUFFileButton, &QPushButton::clicked, this, [this]() {
        const QString fileName = QFileDialog::getOpenFileName(this, i18nc("@title:window", "Select GGUF File"));
        if (!fileName.isEmpty()) {
            // TODO
        }
    });

    auto createModelButton = new QPushButton(i18nc("@action:button", "Create Model"), this);
    createModelButton->setObjectName(u"createModelButton"_s);
    selectModeWidgetLayout->addWidget(createModelButton, 0, Qt::AlignTop);
    connect(createModelButton, &QPushButton::clicked, this, [this]() {
        mOllamaModelCreateFromExistingModelWidget->clear();
        mStackWidget->setCurrentWidget(mOllamaModelCreateFromExistingModelWidget);
    });
    connect(mOllamaModelCreateFromExistingModelWidget,
            &OllamaModelCreateFromExistingModelWidget::cancelRequested,
            this,
            &OllamaModelCreateWidget::createModelDone);
    connect(mOllamaModelCreateFromExistingModelWidget,
            &OllamaModelCreateFromExistingModelWidget::createNewModelDone,
            this,
            &OllamaModelCreateWidget::createModelDone);
    connect(this, &OllamaModelCreateWidget::createModelDone, this, [this]() {
        mStackWidget->setCurrentWidget(mSelectModeWidget);
    });
}

OllamaModelCreateWidget::~OllamaModelCreateWidget() = default;

#include "moc_ollamamodelcreatewidget.cpp"
