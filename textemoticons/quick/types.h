/*
    SPDX-FileCopyrightText: 2024 Joshua Goins <josh@redstrate.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QQmlEngine>

#include <TextEmoticonsCore/EmojiModelManager>
#include <TextEmoticonsCore/EmojiProxyModel>
#include <TextEmoticonsCore/UnicodeEmoticonManager>

struct UnicodeEmoticonManagerForeign {
    Q_GADGET
    QML_ELEMENT
    QML_SINGLETON
    QML_NAMED_ELEMENT(UnicodeEmoticonManager)
    QML_FOREIGN(TextEmoticonsCore::UnicodeEmoticonManager)
};

struct EmojiProxyModelForeign {
    Q_GADGET
    QML_ELEMENT
    QML_NAMED_ELEMENT(EmojiProxyModel)
    QML_FOREIGN(TextEmoticonsCore::EmojiProxyModel)
};

struct EmojiModelManagerForeign {
    Q_GADGET
    QML_ELEMENT
    QML_SINGLETON
    QML_NAMED_ELEMENT(EmojiModelManager)
    QML_FOREIGN(TextEmoticonsCore::EmojiModelManager)
};
