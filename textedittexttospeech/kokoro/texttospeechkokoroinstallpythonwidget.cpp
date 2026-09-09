/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroinstallpythonwidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

using namespace TextEditTextToSpeech;
using namespace Qt::Literals::StringLiterals;
TextToSpeechKokoroInstallPythonWidget::TextToSpeechKokoroInstallPythonWidget(QWidget *parent)
    : QWidget{parent}
    , mPlainTextEdit(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mPlainTextEdit->setObjectName(u"mPlainTextEdit"_s);
    mainLayout->addWidget(mPlainTextEdit);
}

TextToSpeechKokoroInstallPythonWidget::~TextToSpeechKokoroInstallPythonWidget() = default;
#include "moc_texttospeechkokoroinstallpythonwidget.cpp"
