/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineclient.h"
#include "begamotenginedialog.h"
#include "bergamotengineplugin.h"
#include "translator/misc/translatorutil.h"
#include <KLocalizedString>
#include <QPointer>

BergamotEngineClient::BergamotEngineClient(QObject *parent)
    : TextTranslator::TranslatorEngineClient{parent}
{
}

BergamotEngineClient::~BergamotEngineClient() = default;

QString BergamotEngineClient::name() const
{
    return QStringLiteral("bergamot");
}

QString BergamotEngineClient::translatedName() const
{
    return i18n("Bergamot");
}

TextTranslator::TranslatorEnginePlugin *BergamotEngineClient::createTranslator()
{
    return new BergamotEnginePlugin();
}

QMap<TextTranslator::TranslatorUtil::Language, QString> BergamotEngineClient::supportedLanguages()
{
    if (mLanguages.isEmpty()) {
        mLanguages = fillLanguages();
    }
    return mLanguages;
}

bool BergamotEngineClient::hasConfigurationDialog() const
{
    return true;
}

void BergamotEngineClient::showConfigureDialog(QWidget *parentWidget)
{
    QPointer<BegamotEngineDialog> dlg = new BegamotEngineDialog(parentWidget);
    if (dlg->exec()) {
        // TODO
    }
    delete dlg;
}

bool BergamotEngineClient::isSupported(TextTranslator::TranslatorUtil::Language lang) const
{
    // TODO
    return true;
}

#include "moc_bergamotengineclient.cpp"
