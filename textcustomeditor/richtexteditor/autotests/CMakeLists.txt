# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(richtexteditortest.cpp richtexteditortest.h TEST_NAME richtexteditortest
    LINK_LIBRARIES KF${KF_MAJOR_VERSION}::TextCustomEditor Qt::Test Qt::Widgets
)

ecm_add_test(richtexteditfindbartest.cpp richtexteditfindbartest.h TEST_NAME richtexteditfindbartest
    LINK_LIBRARIES KF${KF_MAJOR_VERSION}::TextCustomEditor Qt::Test Qt::Widgets
)
