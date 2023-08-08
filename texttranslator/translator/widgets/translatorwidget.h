/*

  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "texttranslator_export.h"
#include <QPlainTextEdit>
namespace TextTranslator
{
/**
 * @brief The TranslatorTextEdit class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTTRANSLATOR_EXPORT TranslatorTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit TranslatorTextEdit(QWidget *parent = nullptr);

Q_SIGNALS:
    void translateText();

protected:
    void dropEvent(QDropEvent *) override;
};

/**
 * @brief The TranslatorWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTTRANSLATOR_EXPORT TranslatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorWidget(QWidget *parent = nullptr);
    explicit TranslatorWidget(const QString &text, QWidget *parent = nullptr);
    ~TranslatorWidget() override;

    void setTextToTranslate(const QString &);
    void writeConfig();
    void readConfig();
    void setStandalone(bool b);

public Q_SLOTS:
    void slotTranslate();
    void slotCloseWidget();

private:
    TEXTTRANSLATOR_NO_EXPORT void slotFromLanguageChanged(int, bool initialize = false);
    TEXTTRANSLATOR_NO_EXPORT void slotTextChanged();
    TEXTTRANSLATOR_NO_EXPORT void slotInvertLanguage();
    TEXTTRANSLATOR_NO_EXPORT void slotClear();
    TEXTTRANSLATOR_NO_EXPORT void slotTranslateDone();
    TEXTTRANSLATOR_NO_EXPORT void slotTranslateFailed(bool result, const QString &message);
    TEXTTRANSLATOR_NO_EXPORT void slotDebug();
    TEXTTRANSLATOR_NO_EXPORT void slotConfigChanged();

protected:
    bool event(QEvent *e) override;

Q_SIGNALS:
    void toolsWasClosed();

private:
    TEXTTRANSLATOR_NO_EXPORT void init();
    TEXTTRANSLATOR_NO_EXPORT void initLanguage();
    TEXTTRANSLATOR_NO_EXPORT void switchEngine();
    TEXTTRANSLATOR_NO_EXPORT void loadEngineSettings();
    class TranslatorWidgetPrivate;
    std::unique_ptr<TranslatorWidgetPrivate> const d;
};
}
