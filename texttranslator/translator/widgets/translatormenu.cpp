/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatormenu.h"
using namespace Qt::Literals::StringLiterals;

#include "texttranslator_debug.h"
#include "translator/misc/translatorutil.h"
#include "translator/translatorengineloader.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QMenu>

using namespace TextTranslator;
TranslatorMenu::TranslatorMenu(QObject *parent)
    : QObject(parent)
    , mMenu(new QMenu)
{
    mMenu->setObjectName(u"menu"_s);
    mMenu->setTitle(i18n("Translate…"));
    mMenu->setIcon(QIcon::fromTheme(u"translate"_s));
    updateMenu();
}

TranslatorMenu::~TranslatorMenu()
{
    delete mMenu;
}

bool TranslatorMenu::isEmpty() const
{
    return mMenu->isEmpty();
}

void TranslatorMenu::updateMenu()
{
    mMenu->clear();
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), u"Translate"_s);
    const QString engine = groupTranslate.readEntry(u"engine"_s, u"google"_s); // Google by default
    // qDebug() << " engine " << engine;
    const QString currentPluginName = TextTranslator::TranslatorEngineLoader::self()->currentPluginName(engine);
    QString actionText;
    if (!currentPluginName.isEmpty()) {
        actionText = u"[%1] "_s.arg(currentPluginName);
    }
    const auto fromList = groupTranslate.readEntry(u"From"_s, QStringList());
    const auto toList = groupTranslate.readEntry(u"To"_s, QStringList());
    for (const auto &fromLang : fromList) {
        const QString fromLangI18n = TextTranslator::TranslatorUtil::searchI18nFromLanguage(fromLang);
        if (fromLangI18n.isEmpty()) {
            qCWarning(TEXTTRANSLATOR_LOG) << "Impossible to find \"from\" language " << fromLangI18n;
        } else {
            for (const auto &toLang : toList) {
                const QString toLangI18n = TextTranslator::TranslatorUtil::searchI18nFromLanguage(toLang);
                if (toLangI18n.isEmpty()) {
                    qCWarning(TEXTTRANSLATOR_LOG) << "Impossible to find \"to\" language " << fromLangI18n;
                } else {
                    if (fromLangI18n != toLangI18n) {
                        auto action = new QAction(mMenu);
                        action->setText(u"%1%2 -> %3"_s.arg(actionText, fromLangI18n, toLangI18n));
                        connect(action, &QAction::triggered, this, [this, fromLang, toLang]() {
                            Q_EMIT translate(fromLang, toLang, mModelIndex);
                        });
                        mMenu->addAction(action);
                    }
                }
            }
        }
    }
}

const QPersistentModelIndex &TranslatorMenu::modelIndex() const
{
    return mModelIndex;
}

void TranslatorMenu::setModelIndex(const QPersistentModelIndex &newModelIndex)
{
    mModelIndex = newModelIndex;
}

QMenu *TranslatorMenu::menu() const
{
    return mMenu;
}

#include "moc_translatormenu.cpp"
