/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroinstallpythondialog.h"
#include "texttospeechkokoroinstallpythonwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

namespace
{
const char myTextToSpeechKokoroInstallPythonDialogGroupName[] = "TextToSpeechKokoroInstallPythonDialog";
}

using namespace TextEditTextToSpeech;
using namespace Qt::Literals::StringLiterals;
TextToSpeechKokoroInstallPythonDialog::TextToSpeechKokoroInstallPythonDialog(QWidget *parent)
    : QDialog(parent)
    , mKokoroInstallPythonWidget(new TextToSpeechKokoroInstallPythonWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Install Kokoro Package"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);

    mKokoroInstallPythonWidget->setObjectName(u"mKokoroInstallPythonWidget"_s);
    mainLayout->addWidget(mKokoroInstallPythonWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Close, this);
    box->setObjectName(u"box"_s);
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &TextToSpeechKokoroInstallPythonDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &TextToSpeechKokoroInstallPythonDialog::reject);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextToSpeechKokoroInstallPythonDialogGroupName), QSize(400, 300));
}

TextToSpeechKokoroInstallPythonDialog::~TextToSpeechKokoroInstallPythonDialog() = default;

#include "moc_texttospeechkokoroinstallpythondialog.cpp"
