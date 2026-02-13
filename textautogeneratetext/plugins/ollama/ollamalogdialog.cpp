/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamalogdialog.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
const char myOllamaLogDialogGroupName[] = "OllamaLogDialog";
}
using namespace Qt::Literals::StringLiterals;
OllamaLogDialog::OllamaLogDialog(QWidget *parent)
    : QDialog(parent)
    , mPlainTextEdit(new QPlainTextEdit(this))
{
    setWindowTitle(i18nc("@title:window", "Ollama Log"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mPlainTextEdit->setObjectName(u"mPlainTextEdit"_s);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &OllamaLogDialog::reject);
    readConfig();
}

OllamaLogDialog::~OllamaLogDialog()
{
    writeConfig();
}

void OllamaLogDialog::setLog(const QByteArray &ba)
{
    mPlainTextEdit->setPlainText(QString::fromLocal8Bit(ba));
}

void OllamaLogDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaLogDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void OllamaLogDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaLogDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_ollamalogdialog.cpp"
