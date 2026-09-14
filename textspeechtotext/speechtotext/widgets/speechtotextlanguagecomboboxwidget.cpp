/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextlanguagecomboboxwidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextSpeechToText;
SpeechToTextLanguageComboBoxWidget::SpeechToTextLanguageComboBoxWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
}

SpeechToTextLanguageComboBoxWidget::~SpeechToTextLanguageComboBoxWidget() = default;
