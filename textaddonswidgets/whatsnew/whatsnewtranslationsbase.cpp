/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "whatsnewtranslationsbase.h"
#include <QCryptographicHash>
using namespace TextAddonsWidgets;
WhatsNewTranslationsBase::WhatsNewTranslationsBase() = default;

WhatsNewTranslationsBase::~WhatsNewTranslationsBase() = default;

QString WhatsNewTranslationsBase::newFeaturesMD5() const
{
    const auto features = lastNewFeatures();
    if (features.isEmpty()) {
        return {};
    }
    QCryptographicHash md5(QCryptographicHash::Md5);
    for (const KLazyLocalizedString &l : features) {
        md5.addData(l.untranslatedText());
    }
    return QLatin1StringView(md5.result().toBase64());
}
