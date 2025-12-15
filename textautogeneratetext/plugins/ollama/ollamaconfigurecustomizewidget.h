/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class QLineEdit;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaConfigureCustomizeWidget : public QWidget
{
    Q_OBJECT
public:
    struct CustomizeInfo {
        QString vulkanSupport;
        QString cudaVisibleDevice;
        QString rocrVisibleDevice;
        QString overrideGfxVersion;
    };

    explicit OllamaConfigureCustomizeWidget(QWidget *parent = nullptr);
    ~OllamaConfigureCustomizeWidget() override;

    void setCustomizeInfo(const CustomizeInfo &info);
    [[nodiscard]] CustomizeInfo customizeInfo() const;

private:
    QLineEdit *const mVulkanSupportLineEdit;
    QLineEdit *const mCudaVisibleDeviceLineEdit;
    QLineEdit *const mRocrVisibleDeviceLineEdit;
    QLineEdit *const mOverrideGfxVersionLineEdit;
};
