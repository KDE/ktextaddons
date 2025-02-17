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

public:
    static TextEmoticonsCore::UnicodeEmoticonManager *create(QQmlEngine *, QJSEngine *)
    {
        auto inst = TextEmoticonsCore::UnicodeEmoticonManager::self();
        QJSEngine::setObjectOwnership(inst, QJSEngine::ObjectOwnership::CppOwnership);
        return inst;
    }
};

struct EmojiProxyModelForeign {
    Q_GADGET
    QML_ELEMENT
    QML_NAMED_ELEMENT(EmojiSortFilterProxyModel)
    QML_FOREIGN(TextEmoticonsCore::EmojiSortFilterProxyModel)
};

struct EmojiModelManagerForeign {
    Q_GADGET
    QML_ELEMENT
    QML_SINGLETON
    QML_NAMED_ELEMENT(EmojiModelManager)
    QML_FOREIGN(TextEmoticonsCore::EmojiModelManager)

public:
    static TextEmoticonsCore::EmojiModelManager *create(QQmlEngine *, QJSEngine *)
    {
        auto inst = TextEmoticonsCore::EmojiModelManager::self();
        QJSEngine::setObjectOwnership(inst, QJSEngine::ObjectOwnership::CppOwnership);
        return inst;
    }
};
