/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategeneric_private_export.h"
#include <QWidget>
class GenericNetworkModelAvailableListView;
namespace TextAutoGenerateText
{
class TextAutoGenerateModelSearchLineEdit;
}
class GenericNetworkManager;
class GenericNetworkAvailableInfosModel;
class GenericNetworkModelAvailableInfosSortProxyModel;
class GenericNetworkModelAvailableInfoWidget;
class TEXTAUTOGENERATEGENERICNETWORK_TESTS_EXPORT GenericNetworkModelAvailableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GenericNetworkModelAvailableWidget(GenericNetworkManager *manager, QWidget *parent = nullptr);
    ~GenericNetworkModelAvailableWidget() override;

private:
    GenericNetworkModelAvailableListView *const mAvailableListView;
    TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit *const mSearchLineEdit;
    GenericNetworkAvailableInfosModel *const mAvailableInfosModel;
    GenericNetworkModelAvailableInfosSortProxyModel *const mProxyModel;
    GenericNetworkModelAvailableInfoWidget *const mAvailableInfoWidget;
    GenericNetworkManager *const mManager;
};
