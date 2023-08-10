/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorengineplugin.h"
#include <KLocalizedString>
using namespace TextTranslator;

class TextTranslator::TranslatorEnginePluginPrivate
{
public:
    QString mText;
    QString mFrom;
    QString mTo;
    QString mResult;
    QString mJsonDebug;
    bool mHasDebug = false;
};

TranslatorEnginePlugin::TranslatorEnginePlugin(QObject *parent)
    : QObject(parent)
    , d(new TextTranslator::TranslatorEnginePluginPrivate)
{
    d->mHasDebug = !qEnvironmentVariableIsEmpty("TRANSLATING_DEBUGGING");
}

QString TranslatorEnginePlugin::resultTranslate() const
{
    return result();
}

TranslatorEnginePlugin::~TranslatorEnginePlugin() = default;

void TranslatorEnginePlugin::setInputText(const QString &text)
{
    d->mText = text;
}

void TranslatorEnginePlugin::setFrom(const QString &language)
{
    if (d->mFrom != language) {
        d->mFrom = language;
        Q_EMIT languagesChanged();
    }
}

void TranslatorEnginePlugin::setTo(const QString &language)
{
    if (d->mTo != language) {
        d->mTo = language;
        Q_EMIT languagesChanged();
    }
}

void TranslatorEnginePlugin::setResult(const QString &result)
{
    d->mResult = result;
}

void TranslatorEnginePlugin::setJsonDebug(const QString &debug)
{
    d->mJsonDebug = debug;
}

void TranslatorEnginePlugin::clear()
{
    d->mResult.clear();
}

void TranslatorEnginePlugin::appendResult(const QString &result)
{
    d->mResult += result;
}

QString TranslatorEnginePlugin::inputText() const
{
    return d->mText;
}

QString TranslatorEnginePlugin::from() const
{
    return d->mFrom;
}

QString TranslatorEnginePlugin::to() const
{
    return d->mTo;
}

QString TranslatorEnginePlugin::result() const
{
    return d->mResult;
}

QString TranslatorEnginePlugin::jsonDebug() const
{
    return d->mJsonDebug;
}

void TranslatorEnginePlugin::slotError(QNetworkReply::NetworkError error)
{
    QString messageError;
    if (error == QNetworkReply::ServiceUnavailableError) {
        messageError = i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later.");
    }
    Q_EMIT translateFailed(messageError);
}

bool TranslatorEnginePlugin::verifyFromAndToLanguage()
{
    if (d->mTo == d->mFrom) {
        Q_EMIT translateFailed(i18n("You used same language for \'from\' and \'to\' language."));
        return true;
    }
    return false;
}

bool TranslatorEnginePlugin::hasDebug() const
{
    return d->mHasDebug;
}

QString TranslatorEnginePlugin::languageCode(const QString &langStr)
{
    return langStr;
}

#include "moc_translatorengineplugin.cpp"
