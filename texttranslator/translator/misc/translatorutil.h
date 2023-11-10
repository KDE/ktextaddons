/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "texttranslator_export.h"
#include <QString>

class QComboBox;

namespace TextTranslator
{
class TEXTTRANSLATOR_EXPORT TranslatorUtil
{
public:
    TranslatorUtil();

    struct TranslatorSettings {
        QString engine;
        QString from;
        QString to;
    };

    enum Language : int {
        automatic = 0,
        en,
        bs,
        hmong,
        zh,
        zt,
        nl,
        fr,
        de,
        el,
        it,
        ja,
        ko,
        pt,
        ru,
        es,
        af,
        sq,
        ar,
        hy,
        az,
        eu,
        be,
        bg,
        ca,
        hr,
        cs,
        da,
        et,
        tl,
        fi,
        gl,
        ka,
        ht,
        iw,
        hi,
        hu,
        is,
        id,
        ga,
        lv,
        lt,
        mk,
        ms,
        mt,
        no,
        fa,
        pl,
        ro,
        sr,
        sk,
        sl,
        sw,
        sv,
        th,
        tr,
        uk,
        ur,
        vi,
        cy,
        yi,
        lastLanguage = yi
    };
    void addItemToFromComboBox(QComboBox *combo, const QString &languageCode, const QString &translatedStr);

    // Only for test
    [[nodiscard]] static QMap<TranslatorUtil::Language, QString> translatedLanguages();

    [[nodiscard]] static QString loadEngine();
    static void saveEngineSettings(const QString &engineName);
    [[nodiscard]] static QString groupTranslateName();
    [[nodiscard]] static QString engineTranslateName();
    [[nodiscard]] static QString defaultEngineName();
    [[nodiscard]] static QString translatedLanguage(TranslatorUtil::Language lang);
    [[nodiscard]] static QString languageCode(TranslatorUtil::Language lang);
    [[nodiscard]] static QString searchI18nFromLanguage(const QString &langCode);
    [[nodiscard]] static TranslatorUtil::Language stringToLanguage(const QString &str);
};
}
