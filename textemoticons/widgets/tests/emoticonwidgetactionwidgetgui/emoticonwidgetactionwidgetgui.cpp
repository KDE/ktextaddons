/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "emoticonwidgetactionwidgetgui.h"
#include <QApplication>
#include <QTextEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetActionWidgetGui::EmoticonWidgetActionWidgetGui(QWidget *parent)
    : QWidget{parent}
    , mTextEdit(new QTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mainLayout->addWidget(mTextEdit);
}

EmoticonWidgetActionWidgetGui::~EmoticonWidgetActionWidgetGui() = default;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EmoticonWidgetActionWidgetGui window;

    window.show();
    return app.exec();
}
