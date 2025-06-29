/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include <QApplication>
using namespace Qt::Literals::StringLiterals;

#include <QVBoxLayout>
#include <QWidget>

#include <TextEmoticonsCore/EmojiModel>
#include <TextEmoticonsCore/EmojiModelManager>

#include "customemojiiconmanagerguitest.h"
#include "emoticontexteditselector.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        auto mainLayout = new QVBoxLayout(this);
        auto w = new TextEmoticonsWidgets::EmoticonTextEditSelector(this);
        auto customEmojiIconManager = new CustomEmojiIconManagerGuiTest(this);
        w->setCustomEmojiSupport(true);
        TextEmoticonsCore::EmojiModelManager::self()->emojiModel()->setCustomEmojiIconManager(customEmojiIconManager);

        QList<TextEmoticonsCore::CustomEmoji> customEmoji;
        {
            TextEmoticonsCore::CustomEmoji custom;
            custom.setIdentifier(u":custom1:"_s);
            customEmoji.append(custom);
        }
        {
            TextEmoticonsCore::CustomEmoji custom;
            custom.setIdentifier(u":custom2:"_s);
            customEmoji.append(custom);
        }
        {
            TextEmoticonsCore::CustomEmoji custom;
            custom.setIdentifier(u":gif1:"_s);
            custom.setIsAnimatedEmoji(true);
            customEmoji.append(custom);
        }
        TextEmoticonsCore::EmojiModelManager::self()->emojiModel()->setCustomEmojiList(customEmoji);
        w->loadEmoticons();

        mainLayout->addWidget(w);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;

    window.show();
    return app.exec();
}

#include "emoticontexteditselector_customemoji_gui.moc"
