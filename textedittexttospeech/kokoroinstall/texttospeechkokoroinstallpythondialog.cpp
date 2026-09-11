/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroinstallpythondialog.h"
#include "texttospeechkokoroinstallpythonwidget.h"
#include <KLocalizedString>
#include <KStandardGuiItem>
#include <QDialogButtonBox>
#include <QPushButton>
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
    , mCloseButton(new QPushButton(this))
{
    setWindowTitle(i18nc("@title:window", "Install Kokoro Package"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);

    mKokoroInstallPythonWidget->setObjectName(u"mKokoroInstallPythonWidget"_s);
    mainLayout->addWidget(mKokoroInstallPythonWidget);

    auto box = new QDialogButtonBox(this);
    box->setObjectName(u"box"_s);
    mCloseButton->setObjectName(u"mCloseButton"_s);
    box->addButton(mCloseButton, QDialogButtonBox::RejectRole);
    KGuiItem::assign(mCloseButton, KStandardGuiItem::close());
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &TextToSpeechKokoroInstallPythonDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &TextToSpeechKokoroInstallPythonDialog::reject);
    // Closing the dialog would kill pip in the middle of the installation.
    connect(mKokoroInstallPythonWidget, &TextToSpeechKokoroInstallPythonWidget::installDone, mCloseButton, [this]() {
        mCloseButton->setEnabled(true);
    });
    connect(mKokoroInstallPythonWidget, &TextToSpeechKokoroInstallPythonWidget::installFailed, mCloseButton, [this]() {
        mCloseButton->setEnabled(true);
    });
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextToSpeechKokoroInstallPythonDialogGroupName), QSize(400, 300));
}

TextToSpeechKokoroInstallPythonDialog::~TextToSpeechKokoroInstallPythonDialog() = default;

void TextToSpeechKokoroInstallPythonDialog::setModules(const QStringList &modules)
{
    mKokoroInstallPythonWidget->setModules(modules);
}

void TextToSpeechKokoroInstallPythonDialog::startInstall()
{
    mCloseButton->setEnabled(false);
    mKokoroInstallPythonWidget->startInstall();
}

#include "moc_texttospeechkokoroinstallpythondialog.cpp"
