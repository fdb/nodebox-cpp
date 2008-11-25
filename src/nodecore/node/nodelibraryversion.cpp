/*
 * This file is part of NodeBox.
 *
 * Copyright (C) 2008 Frederik De Bleser (frederik@pandora.be)
 *
 * NodeBox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NodeBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NodeBox.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "NodeLibraryVersion.h"

#include <QtCore/QString>

namespace NodeCore {

NodeLibraryVersion::NodeLibraryVersion()
    : m_version_major(0),
      m_version_minor(0),
      m_version_revision(0)
{
}

NodeLibraryVersion::NodeLibraryVersion(int version_major, int version_minor, int version_revision)
    : m_version_major(version_major),
      m_version_minor(version_minor),
      m_version_revision(version_revision)
{
}

QString NodeLibraryVersion::toString()
{
    QString version = QString();
    version.append(QString::number(m_version_major));
    version.append(".");
    version.append(QString::number(m_version_minor));
    version.append(".");
    version.append(QString::number(m_version_revision));
    return version;
}

NodeLibraryVersion& NodeLibraryVersion::operator=(const NodeLibraryVersion& other)
{
        if (this== &other) return *this;
        m_version_major = other.m_version_major;
        m_version_minor = other.m_version_minor;
        m_version_revision = other.m_version_revision;
        return *this;
}

} // namespace NodeCore
