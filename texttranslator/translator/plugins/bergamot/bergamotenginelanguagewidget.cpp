/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginelanguagewidget.h"
#include <KLocalizedString>
#include <QTreeView>
#include <QVBoxLayout>

BergamotEngineLanguageWidget::BergamotEngineLanguageWidget(QWidget *parent)
    : QWidget{parent}
    , mTreeView(new QTreeView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mTreeView->setObjectName(QStringLiteral("mTreeView"));
    // TODO
}

BergamotEngineLanguageWidget::~BergamotEngineLanguageWidget() = default;
