/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
namespace TextSpeechToText
{
/**
 * @brief The SpeechToTextClient class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextClient : public QObject
{
    Q_OBJECT
public:
    explicit SpeechToTextClient(QObject *parent = nullptr);
    ~SpeechToTextClient() override;

    /**
     * @returns the name of the implementing class.
     */
    virtual QString name() const = 0;

    Q_REQUIRED_RESULT virtual bool hasConfigurationDialog() const;

    virtual bool showConfigureDialog(QWidget *parentWidget);
Q_SIGNALS:
    void configureChanged();
};
}
