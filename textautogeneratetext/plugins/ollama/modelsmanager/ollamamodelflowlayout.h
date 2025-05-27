/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QLayout>
#include <QList>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelFlowLayout : public QLayout
{
    Q_OBJECT

public:
    explicit OllamaModelFlowLayout(QWidget *parent = nullptr);
    ~OllamaModelFlowLayout() override;

    [[nodiscard]] int horizontalSpacing() const;
    void setHorizontalSpacing(int horizontalSpacing);

    [[nodiscard]] int verticalSpacing() const;
    void setVerticalSpacing(int verticalSpacing);

    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] QSize minimumSize() const override;

    void addItem(QLayoutItem *item) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    [[nodiscard]] int count() const override;

    [[nodiscard]] Qt::Orientations expandingDirections() const override;
    [[nodiscard]] bool hasHeightForWidth() const override;
    [[nodiscard]] int heightForWidth(int width) const override;

    void setGeometry(const QRect &rect) override;

    void clearAndDeleteWidgets();

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void clear();
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT int doFlow(QRect rect, bool effective) const;
    QList<QLayoutItem *> mItems;
    int mHorizontalSpacing = -1;
    int mVerticalSpacing = -1;
};
