# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(plaintexteditortest.cpp plaintexteditortest.h
    TEST_NAME plaintexteditortest
    LINK_LIBRARIES KF${KF_MAJOR_VERSION}::TextCustomEditor KF${KF_MAJOR_VERSION}::KIOWidgets Qt::Test Qt::Widgets
)

ecm_add_test(plaintexteditfindbartest.cpp plaintexteditfindbartest.h
    TEST_NAME plaintexteditfindbartest
    LINK_LIBRARIES KF${KF_MAJOR_VERSION}::TextCustomEditor KF${KF_MAJOR_VERSION}::KIOWidgets Qt::Test Qt::Widgets
)
