/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewcomboboxwidget.h"
#include <KLocalizedString>
#include <KSeparator>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

using namespace Qt::Literals::StringLiterals;

using namespace TextAddonsWidgets;
WhatsNewComboBoxWidget::WhatsNewComboBoxWidget(QWidget *parent)
    : QWidget{parent}
    , mVersionComboBox(new QComboBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(u"hboxLayout"_s);
    hboxLayout->setContentsMargins({});
    mainLayout->addLayout(hboxLayout);

    auto label = new QLabel(i18nc("@label:textbox", "Version:"), this);
    label->setObjectName(u"label"_s);
    hboxLayout->addWidget(label);

    mVersionComboBox->setObjectName(u"mVersionComboBox"_s);
    hboxLayout->addWidget(mVersionComboBox);
    hboxLayout->addStretch(1);

    auto separator = new KSeparator(this);
    separator->setObjectName(u"separator"_s);
    mainLayout->addWidget(separator);

    connect(mVersionComboBox, &QComboBox::currentIndexChanged, this, &WhatsNewComboBoxWidget::slotCurrentIndexChanged);
}

void WhatsNewComboBoxWidget::addVersion(const QString &name, int identifier)
{
    mVersionComboBox->addItem(name, identifier);
}

WhatsNewComboBoxWidget::~WhatsNewComboBoxWidget() = default;

void WhatsNewComboBoxWidget::initializeVersion(int identifier)
{
    if (const int index = mVersionComboBox->findData(identifier); index != -1) {
        mVersionComboBox->setCurrentIndex(index);
    }
}

void WhatsNewComboBoxWidget::slotCurrentIndexChanged(int index)
{
    if (index == -1) {
        return;
    }
    const int type = mVersionComboBox->itemData(index).toInt();
    Q_EMIT versionChanged(type);
}

void WhatsNewComboBoxWidget::clear()
{
    mVersionComboBox->clear();
}

#include "moc_whatsnewcomboboxwidget.cpp"
