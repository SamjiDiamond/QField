/***************************************************************************
  androidresourcesource.cpp - AndroidResourceSource

 ---------------------
 begin                : 5.7.2016
 copyright            : (C) 2016 by Matthias Kuhn
 email                : matthias@opengis.ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "androidresourcesource.h"
#include "platformutilities.h"

#include <QDir>
#include <QFile>
#include <QSettings>

AndroidResourceSource::AndroidResourceSource( QObject *parent, const QString &prefix )
  : ResourceSource( parent, prefix )
  , mPrefix( prefix )
{
  connect( PlatformUtilities::instance(), &PlatformUtilities::resourceReceived, this, &AndroidResourceSource::handleResourceReceived );
}

void AndroidResourceSource::handleResourceReceived( const QString &path )
{
  disconnect( PlatformUtilities::instance(), &PlatformUtilities::resourceReceived, this, &AndroidResourceSource::handleResourceReceived );

  if ( QSettings().value( QStringLiteral( "QField/nativeCameraLaunched" ), false ).toBool() )
  {
    QSettings().setValue( QStringLiteral( "QField/nativeCameraLaunched" ), false );
  }

  if ( !path.isEmpty() )
  {
    QString relativePath = path;
    relativePath.remove( mPrefix );
    emit resourceReceived( relativePath );
  }
  else
  {
    emit resourceReceived( QString() );
  }
}
