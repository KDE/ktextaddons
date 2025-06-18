/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddinstancewidget.h"
#include "textautogeneratetextinstancecombobox.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

using namespace TextAutoGenerateText;
TextAutoGenerateAddInstanceWidget::TextAutoGenerateAddInstanceWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mInstanceComboBox(new TextAutoGenerateTextInstanceComboBox(manager, this))
    , mNameLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mNameLineEdit->setObjectName(QStringLiteral("mNameLineEdit"));
    mNameLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18nc("@label:textbox", "Name:"), mNameLineEdit);
    KLineEditEventHandler::catchReturnKey(mNameLineEdit);

    mInstanceComboBox->setObjectName(QStringLiteral("mInstanceComboBox"));
    mainLayout->addRow(i18nc("@label:textbox", "Select a Type of Instance:"), mInstanceComboBox);
    connect(mNameLineEdit, &QLineEdit::textChanged, this, [this](const QString &str) {
        Q_EMIT buttonOkEnabled(!str.isEmpty());
    });
}

TextAutoGenerateAddInstanceWidget::~TextAutoGenerateAddInstanceWidget() = default;

TextAutoGenerateTextClient::SupportedServer TextAutoGenerateAddInstanceWidget::selectedInstanceType() const
{
    return mInstanceComboBox->selectedInstanceType();
}

QString TextAutoGenerateAddInstanceWidget::instanceName() const
{
    return mNameLineEdit->text();
}

#include "moc_textautogenerateaddinstancewidget.cpp"
