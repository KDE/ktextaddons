/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroinstallpythondialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace TextEditTextToSpeech;
using namespace Qt::Literals::StringLiterals;
TextToSpeechKokoroInstallPythonDialog::TextToSpeechKokoroInstallPythonDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Install Kokoro Package"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
#if 0
    mConfigWidget->setObjectName(u"configwidget"_s);
    mainLayout->addWidget(mConfigWidget);
#endif

    auto box = new QDialogButtonBox(QDialogButtonBox::Close, this);
    box->setObjectName(u"box"_s);
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &TextToSpeechKokoroInstallPythonDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &TextToSpeechKokoroInstallPythonDialog::reject);
}

TextToSpeechKokoroInstallPythonDialog::~TextToSpeechKokoroInstallPythonDialog() = default;

#include "moc_texttospeechkokoroinstallpythondialog.cpp"
