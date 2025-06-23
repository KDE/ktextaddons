/*
  SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionwidget_gui.h"
using namespace Qt::Literals::StringLiterals;

#include "autocorrectionlineedit.h"
#include "autocorrectiontextedit.h"
#include "autocorrectionwidget.h"
#include "settings/textautocorrectionsettings.h"
#include <TextAutoCorrectionCore/AutoCorrection>

#include <QAction>
#include <QApplication>
#include <QCommandLineParser>
#include <QDialogButtonBox>
#include <QPointer>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>

ConfigureTestDialog::ConfigureTestDialog(TextAutoCorrectionCore::AutoCorrection *autoCorrection, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(u"Configure Autocorrection"_s);
    auto mainLayout = new QVBoxLayout(this);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfigureTestDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfigureTestDialog::reject);

    buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);

    mWidget = new TextAutoCorrectionWidgets::AutoCorrectionWidget(this);
    mainLayout->addWidget(mWidget);
    mainLayout->addWidget(buttonBox);

    mWidget->setAutoCorrection(autoCorrection);
    mWidget->loadConfig();
    connect(okButton, &QPushButton::clicked, this, &ConfigureTestDialog::slotSaveSettings);
}

ConfigureTestDialog::~ConfigureTestDialog() = default;

void ConfigureTestDialog::slotSaveSettings()
{
    mWidget->writeConfig();
}

AutocorrectionTestWidget::AutocorrectionTestWidget(QWidget *parent)
    : QWidget(parent)
    , mConfig(KSharedConfig::openConfig(u"autocorrectionguirc"_s))
{
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setSharedConfig(mConfig);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->load();

    mAutoCorrection = new TextAutoCorrectionCore::AutoCorrection;
    auto lay = new QVBoxLayout(this);
    auto bar = new QToolBar;
    lay->addWidget(bar);
    bar->addAction(u"Configure…"_s, this, &AutocorrectionTestWidget::slotConfigure);
    auto richText = new QAction(u"HTML mode"_s, this);
    richText->setCheckable(true);
    connect(richText, &QAction::toggled, this, &AutocorrectionTestWidget::slotChangeMode);
    bar->addAction(richText);

    mSubject = new TextAutoCorrectionWidgets::AutoCorrectionLineEdit(this);
    mSubject->setAutocorrection(mAutoCorrection);
    lay->addWidget(mSubject);

    mEdit = new TextAutoCorrectionWidgets::AutoCorrectionTextEdit(this);
    mEdit->setAutocorrection(mAutoCorrection);
    lay->addWidget(mEdit);
}

AutocorrectionTestWidget::~AutocorrectionTestWidget()
{
    mAutoCorrection->writeConfig();
    delete mAutoCorrection;
}

void AutocorrectionTestWidget::slotChangeMode(bool mode)
{
    mEdit->setAcceptRichText(mode);
}

void AutocorrectionTestWidget::slotConfigure()
{
    QPointer<ConfigureTestDialog> dlg = new ConfigureTestDialog(mAutoCorrection, this);
    if (dlg->exec()) {
        TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->save();
    }
    delete dlg;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new AutocorrectionTestWidget();
    w->resize(800, 600);

    w->show();
    const int ret = app.exec();
    delete w;
    return ret;
}

#include "moc_autocorrectionwidget_gui.cpp"
