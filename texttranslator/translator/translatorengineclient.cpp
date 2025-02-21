/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorengineclient.h"
#include <KLocalizedString>

using namespace TextTranslator;

TranslatorEngineClient::TranslatorEngineClient(QObject *parent)
    : QObject{parent}
{
}

TranslatorEngineClient::~TranslatorEngineClient() = default;

void TranslatorEngineClient::updateListLanguages()
{
    // Nothing by default
}

bool TranslatorEngineClient::hasConfigurationDialog() const
{
    // False by default
    return false;
}

bool TranslatorEngineClient::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget);
    // Nothing by default
    return false;
}

void TranslatorEngineClient::generateToListFromCurrentToLanguage(const QString &languageCode)
{
    Q_UNUSED(languageCode);
    // Nothing by default
}

bool TranslatorEngineClient::hasInvertSupport() const
{
    // True by default
    return true;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> TranslatorEngineClient::fillLanguages()
{
    QMap<TextTranslator::TranslatorUtil::Language, QString> map;
    for (int i = TextTranslator::TranslatorUtil::Language::automatic; i < TextTranslator::TranslatorUtil::Language::lastLanguage; ++i) {
        if (isSupported(static_cast<TextTranslator::TranslatorUtil::Language>(i))) {
            map.insert(static_cast<TextTranslator::TranslatorUtil::Language>(i),
                       TextTranslator::TranslatorUtil::translatedLanguage(static_cast<TextTranslator::TranslatorUtil::Language>(i)));
        }
    }
    return map;
}

QString TranslatorEngineClient::convertEngineType(TextTranslator::TranslatorEngineClient::EngineType type)
{
    switch (type) {
    case TextTranslator::TranslatorEngineClient::EngineType::Local:
        return i18n("Local");
    case TextTranslator::TranslatorEngineClient::EngineType::Network:
        return i18n("Network");
    }
    Q_UNREACHABLE();
    return {};
}

#include "moc_translatorengineclient.cpp"
