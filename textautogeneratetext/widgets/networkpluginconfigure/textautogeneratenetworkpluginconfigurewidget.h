/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QWidget>
class KPasswordLineEdit;
class QLineEdit;
class QSpinBox;
class QDoubleSpinBox;
class QLabel;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateNetworkPluginConfigureWidget
 * \brief The TextAutoGenerateNetworkPluginConfigureWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateNetworkPluginConfigureWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateNetworkPluginConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a new TextAutoGenerateNetworkPluginConfigureWidget.
     * \param parent The parent widget
     */
    explicit TextAutoGenerateNetworkPluginConfigureWidget(QWidget *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateNetworkPluginConfigureWidget.
     */
    ~TextAutoGenerateNetworkPluginConfigureWidget() override;

    /*!
     * Sets the API key.
     * \param key The API key to set
     */
    void setApiKey(const QString &key);
    /*!
     * Returns the API key.
     * \return The API key
     */
    [[nodiscard]] QString apiKey() const;

    /*!
     * Sets the instance name.
     * \param name The instance name to set
     */
    void setInstanceName(const QString &name);
    /*!
     * Returns the instance name.
     * \return The instance name
     */
    [[nodiscard]] QString instanceName() const;

    /*!
     * Sets the temperature parameter.
     * \param temp The temperature value to set
     */
    void setTemperature(double temp);
    /*!
     * Returns the temperature parameter.
     * \return The temperature value
     */
    [[nodiscard]] double temperature() const;

    /*!
     * Sets the maximum number of tokens.
     * \param tokens The maximum token count to set
     */
    void setMaxTokens(int tokens);
    /*!
     * Returns the maximum number of tokens.
     * \return The maximum token count
     */
    [[nodiscard]] int maxTokens() const;

    /*!
     * Sets the seed value for random number generation.
     * \param tokens The seed value to set
     */
    void setSeed(int tokens);
    /*!
     * Returns the seed value.
     * \return The seed value
     */
    [[nodiscard]] int seed() const;

    /*!
     * Sets the website URL.
     * \param url The website URL to set
     */
    void setWebSiteUrl(const QString &url);
    /*!
     * Sets the description text.
     * \param description The description to set
     */
    void setDescription(const QString &description);

private:
    KPasswordLineEdit *const mApiKey;
    QLineEdit *const mInstanceName;
    QSpinBox *const mMaxToken;
    QDoubleSpinBox *const mTemperature;
    QSpinBox *const mSeed;
    QLabel *const mWebSite;
    QLabel *const mDescription;
};
}
