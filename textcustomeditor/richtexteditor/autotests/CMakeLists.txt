# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(richtexteditortest.cpp richtexteditortest.h TEST_NAME richtexteditortest
    LINK_LIBRARIES KF6::TextCustomEditor Qt::Test Qt::Widgets
)

ecm_add_test(richtexteditfindbartest.cpp richtexteditfindbartest.h TEST_NAME richtexteditfindbartest
    LINK_LIBRARIES KF6::TextCustomEditor Qt::Test Qt::Widgets
)
