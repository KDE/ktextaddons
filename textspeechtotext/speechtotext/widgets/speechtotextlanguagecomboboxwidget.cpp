/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextlanguagecomboboxwidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextSpeechToText;
SpeechToTextLanguageComboBoxWidget::SpeechToTextLanguageComboBoxWidget(QWidget *parent)
    : QWidget{parent}
    , mLanguageLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18n("Language:"), this);
    label->setObjectName(u"label"_s);
    mainLayout->addWidget(label);

    mLanguageLineEdit->setObjectName(u"mLanguageLineEdit"_s);
    mainLayout->addWidget(mLanguageLineEdit);
}

SpeechToTextLanguageComboBoxWidget::~SpeechToTextLanguageComboBoxWidget() = default;

QString SpeechToTextLanguageComboBoxWidget::language() const
{
    return mLanguageLineEdit->text();
}
#include "moc_speechtotextlanguagecomboboxwidget.cpp"
