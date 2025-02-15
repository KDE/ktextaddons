/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "texttranslator_export.h"
#include <QWidget>
class QListView;
class QLineEdit;
class QLabel;
class QStandardItemModel;
namespace TextTranslator
{
/**
 * @brief The TranslatorConfigureLanguageListWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTTRANSLATOR_EXPORT TranslatorConfigureLanguageListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorConfigureLanguageListWidget(const QString &labelText, QWidget *parent = nullptr);
    ~TranslatorConfigureLanguageListWidget() override;

    void clear();

    void addItem(const QString &translatedStr, const QString &languageCode);

    [[nodiscard]] QStringList selectedLanguages() const;
    void setSelectedLanguages(const QStringList &list);

private:
    enum LanguageData {
        LanguageCode = Qt::UserRole + 1,
    };
    QListView *const mLanguageListWidget;
    QLineEdit *const mListSearchLine;
    QLabel *const mLabel;
    QStandardItemModel *const mModel;
};
}
