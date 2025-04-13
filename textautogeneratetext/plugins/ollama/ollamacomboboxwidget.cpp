/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacomboboxwidget.h"
#include <KLocalizedString>
#include <QComboBox>
#include <QHBoxLayout>
#include <QToolButton>

OllamaComboBoxWidget::OllamaComboBoxWidget(QWidget *parent)
    : QWidget{parent}
    , mModelComboBox(new QComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mModelComboBox->setObjectName(QStringLiteral("mModelComboBox"));
    mainLayout->addWidget(mModelComboBox);

    auto buttonReloadSettings = new QToolButton(this);
    buttonReloadSettings->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
    buttonReloadSettings->setObjectName(QStringLiteral("buttonReloadSettings"));
    buttonReloadSettings->setToolTip(i18nc("@info:tooltip", "Reload Model"));
    mainLayout->addWidget(buttonReloadSettings);
    connect(buttonReloadSettings, &QToolButton::clicked, this, &OllamaComboBoxWidget::reloadModel);
}

OllamaComboBoxWidget::~OllamaComboBoxWidget() = default;

void OllamaComboBoxWidget::setModels(const QStringList &lst)
{
    mModelComboBox->clear();
    mModelComboBox->addItems(lst);
    mModelComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

void OllamaComboBoxWidget::setCurrentModel(const QString &str)
{
    const int index = mModelComboBox->findText(str);
    if (index >= 0) {
        mModelComboBox->setCurrentIndex(index);
    }
}

QString OllamaComboBoxWidget::currentModel() const
{
    return mModelComboBox->currentText();
}

#include "moc_ollamacomboboxwidget.cpp"
