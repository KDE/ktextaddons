/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "texttranslator_export.h"
#include <QWidget>
#include <TextTranslator/TranslatorUtil>
namespace TextTranslator
{
/**
 * @brief The TranslatorConfigureListsWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTTRANSLATOR_EXPORT TranslatorConfigureListsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorConfigureListsWidget(QWidget *parent = nullptr);
    ~TranslatorConfigureListsWidget() override;

    void save();
    void load();

private:
    TEXTTRANSLATOR_NO_EXPORT void slotEngineSettingsChanged(const QString &engineName);
    TEXTTRANSLATOR_NO_EXPORT void loadLanguagesList();
    TEXTTRANSLATOR_NO_EXPORT void fillLanguages(const QMap<TextTranslator::TranslatorUtil::Language, QString> &listLanguage);
    TEXTTRANSLATOR_NO_EXPORT void fillFromToLanguages(const QMap<TextTranslator::TranslatorUtil::Language, QString> &listFromLanguage,
                                                      const QMap<TextTranslator::TranslatorUtil::Language, QString> &listToLanguage);
    TEXTTRANSLATOR_NO_EXPORT void slotEngineChanged(const QString &engine);
    class TranslatorConfigureListsWidgetPrivate;
    std::unique_ptr<TranslatorConfigureListsWidgetPrivate> const d;
};
}
