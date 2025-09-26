/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "emoticonwidgetactionwidgetgui.h"
#include <QApplication>
#include <QContextMenuEvent>
#include <QMenu>
#include <QTextEdit>
#include <QVBoxLayout>
#include <TextEmoticonsWidgets/EmoticonWidgetAction>
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetActionWidgetGui::EmoticonWidgetActionWidgetGui(QWidget *parent)
    : QWidget{parent}
    , mTextEdit(new EmoticonWidgetTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mainLayout->addWidget(mTextEdit);
}

EmoticonWidgetActionWidgetGui::~EmoticonWidgetActionWidgetGui() = default;

EmoticonWidgetTextEdit::EmoticonWidgetTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
}

EmoticonWidgetTextEdit::~EmoticonWidgetTextEdit() = default;

void EmoticonWidgetTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = createStandardContextMenu();
    auto emoticonAction = new TextEmoticonsWidgets::EmoticonWidgetAction({}, this);
    menu->addAction(emoticonAction);
    menu->exec(event->globalPos());
    delete menu;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EmoticonWidgetActionWidgetGui window;

    window.show();
    return app.exec();
}
