/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddmcpserverwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAddMcpServerWidget::TextAutoGenerateAddMcpServerWidget(QWidget *parent)
    : QWidget{parent}
    , mServerNameLineEdit(new QLineEdit(this))
    , mServerUrlLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mServerNameLineEdit->setObjectName(u"mServerNameLineEdit"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Name:"), mServerNameLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerNameLineEdit);

    mServerUrlLineEdit->setObjectName(u"mServerUrlLineEdit"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Url:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);
    mServerUrlLineEdit->setClearButtonEnabled(true);
    mServerNameLineEdit->setClearButtonEnabled(true);

    connect(mServerNameLineEdit, &QLineEdit::textChanged, this, &TextAutoGenerateAddMcpServerWidget::checkValidSettings);
    connect(mServerUrlLineEdit, &QLineEdit::textChanged, this, &TextAutoGenerateAddMcpServerWidget::checkValidSettings);
}

TextAutoGenerateAddMcpServerWidget::~TextAutoGenerateAddMcpServerWidget() = default;

void TextAutoGenerateAddMcpServerWidget::checkValidSettings()
{
    Q_EMIT buttonOkEnabled(!mServerNameLineEdit->text().trimmed().isEmpty() && !mServerUrlLineEdit->text().trimmed().isEmpty());
}

void TextAutoGenerateAddMcpServerWidget::setServerWidgetInfo(const McpServerWidgetInfo &info)
{
    mServerNameLineEdit->setText(info.name);
    mServerUrlLineEdit->setText(info.serverUrl);
}

TextAutoGenerateAddMcpServerWidget::McpServerWidgetInfo TextAutoGenerateAddMcpServerWidget::serverWidgetInfo() const
{
    const TextAutoGenerateAddMcpServerWidget::McpServerWidgetInfo info{
        .name = mServerNameLineEdit->text(),
        .serverUrl = mServerUrlLineEdit->text(),
    };
    return info;
}

#include "moc_textautogenerateaddmcpserverwidget.cpp"
