/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateaddmcpserverdialog.h"
#include "textautogenerateaddmcpserverwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAddMcpServerDialog::TextAutoGenerateAddMcpServerDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateAddMcpServerWidget(new TextAutoGenerateAddMcpServerWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Server"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mTextAutoGenerateAddMcpServerWidget->setObjectName(u"mTextAutoGenerateAddMcpServerWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateAddMcpServerWidget);
    auto button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    auto buttonOk = button->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateAddMcpServerDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateAddMcpServerDialog::accept);
    connect(mTextAutoGenerateAddMcpServerWidget, &TextAutoGenerateAddMcpServerWidget::buttonOkEnabled, this, [buttonOk](bool state) {
        buttonOk->setEnabled(state);
    });
}

TextAutoGenerateAddMcpServerDialog::~TextAutoGenerateAddMcpServerDialog() = default;

void TextAutoGenerateAddMcpServerDialog::setServerWidgetInfo(const TextAutoGenerateAddMcpServerWidget::McpServerWidgetInfo &info)
{
    mTextAutoGenerateAddMcpServerWidget->setServerWidgetInfo(info);
}

TextAutoGenerateAddMcpServerWidget::McpServerWidgetInfo TextAutoGenerateAddMcpServerDialog::serverWidgetInfo() const
{
    return mTextAutoGenerateAddMcpServerWidget->serverWidgetInfo();
}

#include "moc_textautogenerateaddmcpserverdialog.cpp"
