/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallpythondialog.h"
#include "whisperspeechtotextinstallpythonwidget.h"
#include <KLocalizedString>
#include <KStandardGuiItem>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

namespace
{
const char myWhisperSpeechToTextInstallPythonDialogGroupName[] = "WhisperSpeechToTextInstallPythonDialog";
}

using namespace Qt::Literals::StringLiterals;

WhisperSpeechToTextInstallPythonDialog::WhisperSpeechToTextInstallPythonDialog(QWidget *parent)
    : QDialog(parent)
    , mWhisperInstallPythonWidget(new WhisperSpeechToTextInstallPythonWidget(this))
    , mCloseButton(new QPushButton(this))
{
    setWindowTitle(i18nc("@title:window", "Install Whisper Package"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mWhisperInstallPythonWidget->setObjectName(u"mWhisperInstallPythonWidget"_s);
    mainLayout->addWidget(mWhisperInstallPythonWidget);

    auto box = new QDialogButtonBox(this);
    box->setObjectName(u"box"_s);
    mCloseButton->setObjectName(u"mCloseButton"_s);
    box->addButton(mCloseButton, QDialogButtonBox::RejectRole);
    KGuiItem::assign(mCloseButton, KStandardGuiItem::close());
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &WhisperSpeechToTextInstallPythonDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &WhisperSpeechToTextInstallPythonDialog::reject);
    // Closing the dialog would kill pip in the middle of the installation.
    connect(mWhisperInstallPythonWidget, &WhisperSpeechToTextInstallPythonWidget::installInProgress, mCloseButton, [this](bool status) {
        mCloseButton->setEnabled(!status);
    });
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myWhisperSpeechToTextInstallPythonDialogGroupName), QSize(400, 300));
}

WhisperSpeechToTextInstallPythonDialog::~WhisperSpeechToTextInstallPythonDialog() = default;

void WhisperSpeechToTextInstallPythonDialog::setModules(const QStringList &modules)
{
    mWhisperInstallPythonWidget->setModules(modules);
}

void WhisperSpeechToTextInstallPythonDialog::startInstall()
{
    mWhisperInstallPythonWidget->startInstall();
}

#include "moc_whisperspeechtotextinstallpythondialog.cpp"
