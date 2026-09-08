/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamalogdialog.h"
#include "ollamalogtextedit.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myOllamaLogDialogGroupName[] = "OllamaLogDialog";
}
using namespace Qt::Literals::StringLiterals;
OllamaLogDialog::OllamaLogDialog(QWidget *parent)
    : QDialog(parent)
    , mPlainTextEdit(new OllamaLogTextEdit(this))
{
    setWindowTitle(i18nc("@title:window", "Ollama Log"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mPlainTextEdit->setObjectName(u"mPlainTextEdit"_s);
    mainLayout->addWidget(mPlainTextEdit);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &OllamaLogDialog::reject);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myOllamaLogDialogGroupName), QSize(400, 300));
}

OllamaLogDialog::~OllamaLogDialog() = default;

void OllamaLogDialog::setLog(const QByteArray &ba)
{
    mPlainTextEdit->setPlainText(QString::fromLocal8Bit(ba));
}

#include "moc_ollamalogdialog.cpp"
