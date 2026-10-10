/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateelicitationdialog.h"
#include "widgets/mcp/textautogenerateelicitationwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateElicitationDialog::TextAutoGenerateElicitationDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateElicitationWidget(new TextAutoGenerateElicitationWidget(this))
{
    // TODO add server name
    setWindowTitle(i18nc("@title:window", "Request from %1"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateElicitationWidget->setObjectName(u"mTextAutoGenerateElicitationWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateElicitationWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
}

TextAutoGenerateElicitationDialog::~TextAutoGenerateElicitationDialog() = default;

#include "moc_textautogenerateelicitationdialog.cpp"
