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

#ifndef NodeLibraryVersion_h
#define NodeLibraryVersion_h

#include <QtCore/QString>


namespace NodeCore {

// See http://en.wikipedia.org/wiki/Software_versioning
// GNU version numbering scheme
class NodeLibraryVersion
{
public:
    NodeLibraryVersion();
    NodeLibraryVersion(int version_major, int version_minor, int version_revision);

    int major() { return m_version_major; }
    int minor() { return m_version_minor; }
    int revision() { return m_version_revision; }
    QString toString();

    NodeLibraryVersion& operator=(const NodeLibraryVersion& other);

private:
    int m_version_major;
    int m_version_minor;
    int m_version_revision;
};

} // namespace NodeCore

#endif // NodeLibraryVersion_h
