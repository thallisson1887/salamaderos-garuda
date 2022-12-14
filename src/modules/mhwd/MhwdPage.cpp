/*
 *  This file is part of Garuda Settings Manager.
 *
 *  Roland Singer <roland@manjaro.org>
 *  Ramon Buldó <ramon@manjaro.org>
 *
 *  Garuda Settings Manager is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Garuda Settings Manager is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Garuda Settings Manager.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MhwdCommon.h"
#include "MhwdPage.h"
#include "ui_PageMhwd.h"

MhwdPage::MhwdPage( QWidget* parent ) :
    PageWidget( parent ),
    ui( new Ui::PageMhwd )
{
    ui->setupUi( this );
    setTitle( MhwdCommon::getTitle() );
    QPixmap pix=QIcon::fromTheme("video-display").pixmap(48), QIcon(":/images/resources/gpudriver.png");
    setIcon( pix );
    setShowApplyButton( false );
    setName( MhwdCommon::getName() );

    ui->treeWidget->setContextMenuPolicy( Qt::CustomContextMenu );
    ui->treeWidget->setColumnWidth( 0, 450 );
    ui->treeWidget->setColumnWidth( 1, 100 );
    ui->treeWidget->setColumnWidth( 2, 100 );

    // Context menu actions and icons
   // ui->installAction->setIcon( QIcon::fromTheme( "list-add", QIcon( ":/icons/add.png" ) ) );
   // ui->removeAction->setIcon( QIcon::fromTheme( "list-remove", QIcon( ":/icons/remove.png" ) ) );
   // ui->reinstallAction->setIcon( QIcon::fromTheme( "view-refresh",  QIcon( ":/icons/restore.png" ) ) );

    ui->buttonInstallFree->setText( MhwdCommon::getButtonFreeText() );
    ui->buttonInstallNonFree->setText( MhwdCommon::getButtonNonFreeText() );

    // Connect signals and slots
    connect( ui->buttonInstallFree, &QPushButton::clicked,
             [=] ( )
    {
        MhwdCommon::installFreeConfiguration();
        load();
    } );
    connect( ui->buttonInstallNonFree, &QPushButton::clicked,
             [=] ( )
    {
        MhwdCommon::installNonFreeConfiguration();
        load();
    } );
    connect( ui->installAction, &QAction::triggered,
             [=] ( bool checked )
    {
        Q_UNUSED( checked )
        QString configuration = ui->treeWidget->currentItem()->text( 0 );
        MhwdCommon::installConfiguration( configuration );
        load();
    } );
    connect( ui->reinstallAction, &QAction::triggered,
             [=] ( bool checked )
    {
        Q_UNUSED( checked )
        QString configuration = ui->treeWidget->currentItem()->text( 0 );
        MhwdCommon::reinstallConfiguration( configuration );
        load();
    } );
    connect( ui->removeAction, &QAction::triggered,
             [=] ( bool checked )
    {
        Q_UNUSED( checked )
        QString configuration = ui->treeWidget->currentItem()->text( 0 );
        MhwdCommon::removeConfiguration( configuration );
        load();
    } );
    connect( ui->treeWidget, &QTreeWidget::customContextMenuRequested,
             [=] ( const QPoint &pos )
    {
        MhwdCommon::showItemContextMenu( ui, pos );
    } );
    connect( ui->checkBoxShowAll, &QCheckBox::toggled,
             this, &MhwdPage::load );
    connect( ui->checkBoxShowDangerous, &QCheckBox::toggled,
             this, &MhwdPage::load );
}


MhwdPage::~MhwdPage()
{
    delete ui;
}


void
MhwdPage::load()
{
    MhwdCommon::load( ui );
    QApplication::restoreOverrideCursor();
}
