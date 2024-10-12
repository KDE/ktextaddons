/*
    SPDX-FileCopyrightText: None

    SPDX-License-Identifier: CC0-1.0
*/
// Generated from update-emoji-data.py
#include "emojicategory.h"

#include <KLazyLocalizedString>

const QStringList &getCategoryNames()
{
    static const QStringList names = {
        QString::fromUtf8(kli18nc("Emoji Category", "Smileys and Emotion").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "People and Body").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "Component").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "Animals and Nature").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "Food and Drink").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "Travel and Places").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "Activities").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "Objects").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "Symbols").untranslatedText()),
        QString::fromUtf8(kli18nc("Emoji Category", "Flags").untranslatedText()),
    };
    return names;
}

const QStringList &geti18nCategoryNames()
{
    static const QStringList names = {
        i18nc("Emoji Category", "Smileys and Emotion"),
        i18nc("Emoji Category", "People and Body"),
        i18nc("Emoji Category", "Component"),
        i18nc("Emoji Category", "Animals and Nature"),
        i18nc("Emoji Category", "Food and Drink"),
        i18nc("Emoji Category", "Travel and Places"),
        i18nc("Emoji Category", "Activities"),
        i18nc("Emoji Category", "Objects"),
        i18nc("Emoji Category", "Symbols"),
        i18nc("Emoji Category", "Flags"),
    };
    return names;
}
