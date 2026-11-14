/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

// Module header for qdoc PCH
#include "common/grammaraction.h"
#include "common/grammarerror.h"
#include "common/grammarresulttextedit.h"
#include "common/grammarresultutil.h"
#include "common/grammarresultwidget.h"
#include "grammalecte/grammalecteconfigdialog.h"
#include "grammalecte/grammalecteconfigwidget.h"
#include "grammalecte/grammalectegenerateconfigoptionjob.h"
#include "grammalecte/grammalectegrammarerror.h"
#include "grammalecte/grammalectemanager.h"
#include "grammalecte/grammalecteparser.h"
#include "grammalecte/grammalecteresultjob.h"
#include "grammalecte/grammalecteresultwidget.h"
#include "grammalecte/grammalecteurlrequesterwidget.h"
#include "languagetool/languageinfo.h"
#include "languagetool/languagetoolcombobox.h"
#include "languagetool/languagetoolconfigdialog.h"
#include "languagetool/languagetoolconfigwidget.h"
#include "languagetool/languagetoolgetlistoflanguagejob.h"
#include "languagetool/languagetoolgrammarerror.h"
#include "languagetool/languagetoollistoflanguagesparser.h"
#include "languagetool/languagetoolmanager.h"
#include "languagetool/languagetoolparser.h"
#include "languagetool/languagetoolresultjob.h"
#include "languagetool/languagetoolresultwidget.h"
#include "languagetool/languagetoolupdatecombobox.h"
#include "textgrammarcheckprivate_export.h"
