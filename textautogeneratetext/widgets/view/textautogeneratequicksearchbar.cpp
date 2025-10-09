/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequicksearchbar.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateQuickSearchBar::TextAutoGenerateQuickSearchBar(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mainLayout->addWidget(mSearchLineEdit);
    const auto shortcut = QKeySequence(Qt::CTRL | Qt::Key_K);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search… (%1)", shortcut.toString(QKeySequence::NativeText)));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
}

TextAutoGenerateQuickSearchBar::~TextAutoGenerateQuickSearchBar() = default;

#include "moc_textautogeneratequicksearchbar.cpp"
