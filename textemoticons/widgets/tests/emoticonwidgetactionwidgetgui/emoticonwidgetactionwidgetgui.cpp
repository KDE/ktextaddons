/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "emoticonwidgetactionwidgetgui.h"
#include "emoticontexteditselector.h"
#include <QApplication>
#include <QContextMenuEvent>
#include <QMenu>
#include <QStandardPaths>
#include <QTextEdit>
#include <QVBoxLayout>
#include <TextEmoticonsCore/EmojiModelManager>
#include <TextEmoticonsWidgets/EmoticonWidgetAction>

using namespace Qt::Literals::StringLiterals;
EmoticonWidgetActionWidgetGui::EmoticonWidgetActionWidgetGui(QWidget *parent)
    : QWidget{parent}
    , mTextEdit(new EmoticonWidgetTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mainLayout->addWidget(mTextEdit);
    QFont f = mTextEdit->font();
    f.setPointSize(24);
    mTextEdit->setFont(f);
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
    auto emoticonAction = new TextEmoticonsWidgets::EmoticonWidgetAction(this);
    connect(emoticonAction, &TextEmoticonsWidgets::EmoticonWidgetAction::insertEmoji, this, [this](const QString &str) {
        insertPlainText(str);
    });
    connect(emoticonAction, &TextEmoticonsWidgets::EmoticonWidgetAction::insertEmojiIdentifier, this, [](const QString &identifier) {
        TextEmoticonsCore::EmojiModelManager::self()->addIdentifier(identifier);
    });

    connect(emoticonAction, &TextEmoticonsWidgets::EmoticonWidgetAction::selectEmoji, this, [this]() {
        auto mEmoticonMenuWidget = new TextEmoticonsWidgets::EmoticonTextEditSelector(this);
        mEmoticonMenuWidget->setWindowFlag(Qt::Popup);
        mEmoticonMenuWidget->forceLineEditFocus();
        mEmoticonMenuWidget->loadEmoticons();
        mEmoticonMenuWidget->setAttribute(Qt::WA_DeleteOnClose);
        mEmoticonMenuWidget->show();
        connect(mEmoticonMenuWidget, &TextEmoticonsWidgets::EmoticonTextEditSelector::insertEmojiIdentifier, this, [this](const QString &id) {
            // TODO
        });
    });
    menu->addSeparator();
    menu->addAction(emoticonAction);
    menu->exec(event->globalPos());
    delete menu;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EmoticonWidgetActionWidgetGui window;
    QStandardPaths::setTestModeEnabled(true);
    window.show();
    return app.exec();
}

#include "moc_emoticonwidgetactionwidgetgui.cpp"
