/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "yandexengineclient.h"
#include "translator/misc/translatorutil.h"
#include "yandexengineplugin.h"
#include <KLocalizedString>

YandexEngineClient::YandexEngineClient(QObject *parent)
    : TextTranslator::TranslatorEngineClient{parent}
{
}

YandexEngineClient::~YandexEngineClient() = default;

QString YandexEngineClient::name() const
{
    return QStringLiteral("yandex");
}

QString YandexEngineClient::translatedName() const
{
    return i18n("Yandex");
}

TextTranslator::TranslatorEnginePlugin *YandexEngineClient::createTranslator()
{
    return new YandexEnginePlugin();
}

QMap<TextTranslator::TranslatorUtil::Language, QString> YandexEngineClient::supportedFromLanguages()
{
    if (mFromLanguages.isEmpty()) {
        mFromLanguages = fillLanguages();
    }
    return mFromLanguages;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> YandexEngineClient::supportedToLanguages()
{
    return supportedFromLanguages();
}

TextTranslator::TranslatorEngineClient::EngineType YandexEngineClient::engineType() const
{
    return TextTranslator::TranslatorEngineClient::Network;
}

bool YandexEngineClient::isSupported(TextTranslator::TranslatorUtil::Language lang) const
{
    switch (lang) {
    case TextTranslator::TranslatorUtil::tl:
        return false;
    default:
        break;
    }
    return true;
}

#include "moc_yandexengineclient.cpp"
