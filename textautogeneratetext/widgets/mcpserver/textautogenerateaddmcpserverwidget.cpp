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

    mServerUrlLineEdit->setObjectName(u"mServerNameLineEdit"_s);
    mainLayout->addRow(i18nc("@label:textbox", "Url:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);

    connect(mServerNameLineEdit, &QLineEdit::textChanged, this, [this](const QString &text) {
        Q_EMIT buttonOkEnabled(!text.trimmed().isEmpty());
    });
}

TextAutoGenerateAddMcpServerWidget::~TextAutoGenerateAddMcpServerWidget() = default;
#include "moc_textautogenerateaddmcpserverwidget.cpp"
