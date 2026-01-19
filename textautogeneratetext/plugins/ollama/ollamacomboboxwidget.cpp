/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacomboboxwidget.h"
#include "modelsmanager/ollamashowmodelinfobutton.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <QComboBox>
#include <QHBoxLayout>
#include <QToolButton>

OllamaComboBoxWidget::OllamaComboBoxWidget(QWidget *parent)
    : QWidget{parent}
    , mModelComboBox(new QComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mModelComboBox->setObjectName(u"mModelComboBox"_s);
    mainLayout->addWidget(mModelComboBox);

    auto buttonReloadSettings = new QToolButton(this);
    buttonReloadSettings->setIcon(QIcon::fromTheme(u"view-refresh"_s));
    buttonReloadSettings->setObjectName(u"buttonReloadSettings"_s);
    buttonReloadSettings->setToolTip(i18nc("@info:tooltip", "Reload Model"));
    mainLayout->addWidget(buttonReloadSettings);
    connect(buttonReloadSettings, &QToolButton::clicked, this, &OllamaComboBoxWidget::reloadModel);

    auto showModelInfoButton = new OllamaShowModelInfoButton(this);
    showModelInfoButton->setObjectName(u"showModelInfoButton"_s);
    mainLayout->addWidget(showModelInfoButton);
    connect(showModelInfoButton, &OllamaShowModelInfoButton::showModelInfoRequested, this, [this]() {
        if (!currentModel().isEmpty()) {
            Q_EMIT showModelInfoRequested(currentModel());
        }
    });
}

OllamaComboBoxWidget::~OllamaComboBoxWidget() = default;

void OllamaComboBoxWidget::setModels(const QList<TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> &lst)
{
    mModelComboBox->clear();
    for (const auto &i : lst) {
        mModelComboBox->addItem(i.modelName, i.identifier);
    }
    mModelComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

void OllamaComboBoxWidget::setCurrentModel(const QString &str)
{
    const int index = mModelComboBox->findData(str);
    if (index >= 0) {
        mModelComboBox->setCurrentIndex(index);
    }
}

QString OllamaComboBoxWidget::currentModel() const
{
    return mModelComboBox->currentData().toString();
}

#include "moc_ollamacomboboxwidget.cpp"
