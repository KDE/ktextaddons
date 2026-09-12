/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textedittexttospeech_kokoroinstall_private_export.h"
#include <QComboBox>
#include <QStringList>

namespace TextEditTextToSpeech
{
class KOKOROINSTALLTEXTTOSPEECH_TESTS_EXPORT TextToSpeechKokoroVoiceComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroVoiceComboBox(QWidget *parent = nullptr);
    ~TextToSpeechKokoroVoiceComboBox() override;

    [[nodiscard]] QStringList selectedVoices() const;
    void setSelectedVoices(const QStringList &identifiers);

Q_SIGNALS:
    void selectedVoicesChanged(const QStringList &identifiers);

protected:
    [[nodiscard]] bool eventFilter(QObject *watched, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void fill();
    void toggleItem(const QModelIndex &index);
    void updateDisplayText();

    bool mUpdatingSelection = false;
};
}
