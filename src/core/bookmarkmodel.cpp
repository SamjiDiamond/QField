/***************************************************************************
                            featuremodel.cpp
                              -------------------
              begin                : 10.12.2014
              copyright            : (C) 2014 by Matthias Kuhn
              email                : matthias (at) opengis.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "bookmarkmodel.h"

#include <qgsgeometry.h>

BookmarkModel::BookmarkModel( QgsBookmarkManager *manager, QgsBookmarkManager *projectManager, QObject *parent )
  : QSortFilterProxyModel( parent )
{
  mModel = std::make_unique<QgsBookmarkManagerModel>( manager, projectManager, this );
  setSourceModel( mModel.get() );
}

QVariant BookmarkModel::data( const QModelIndex &index, int role ) const
{
  QModelIndex sourceIndex = mapToSource( index );
  if ( !sourceIndex.isValid() )
    return QVariant();

  switch ( role )
  {
    case BookmarkModel::BookmarkId:
      return mModel->data( sourceIndex, QgsBookmarkManagerModel::RoleId );

    case BookmarkModel::BookmarkName:
      return mModel->data( sourceIndex, QgsBookmarkManagerModel::RoleName );

    case BookmarkModel::BookmarkPoint:
    {
      QgsReferencedRectangle rect = mModel->data( sourceIndex, QgsBookmarkManagerModel::RoleExtent ).value< QgsReferencedRectangle >();
      QgsGeometry geom( new QgsPoint( rect.center() ) );
      return geom;
    }

    case BookmarkModel::BookmarkCrs:
    {
      QgsReferencedRectangle rect = mModel->data( sourceIndex, QgsBookmarkManagerModel::RoleExtent ).value< QgsReferencedRectangle >();
      return rect.crs();
    }
  }

  return QVariant();
}

QHash<int, QByteArray> BookmarkModel::roleNames() const
{
  QHash<int, QByteArray> roleNames = QAbstractProxyModel::roleNames();
  roleNames[BookmarkModel::BookmarkId] = "BookmarkId";
  roleNames[BookmarkModel::BookmarkName] = "BookmarkName";
  roleNames[BookmarkModel::BookmarkPoint] = "BookmarkPoint";
  roleNames[BookmarkModel::BookmarkCrs] = "BookmarkCrs";
  return roleNames;
}

void BookmarkModel::setMapSettings( QgsQuickMapSettings *mapSettings )
{
  if ( mMapSettings == mapSettings )
    return;

  mMapSettings = mapSettings;

  emit mapSettingsChanged();
}

void BookmarkModel::setExtentFromBookmark( const QModelIndex &index )
{
  QModelIndex sourceIndex = mapToSource( index );
  if ( !sourceIndex.isValid() || !mMapSettings )
    return;

  QgsReferencedRectangle rect = mModel->data( sourceIndex, QgsBookmarkManagerModel::RoleExtent ).value< QgsReferencedRectangle >();
  mMapSettings->setExtent( rect );
}
