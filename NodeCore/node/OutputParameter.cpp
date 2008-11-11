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

#include "Connection.h"
#include "OutputParameter.h"

namespace NodeCore {

OutputParameter::OutputParameter(ParameterType* type, Node* node)
    : Parameter(type, node)
{
    Q_ASSERT(type->isOutputParameter());
}

OutputParameter::~OutputParameter()
{
}

/*! Mark all downstream connections dirty. */
 void OutputParameter::markDirtyDownstream()
 {
     for(int i=0; i<m_downstreams.size(); i++) {
         Connection* conn = m_downstreams[i];
         conn->markDirtyDownstream();
     }
 }

/*! Copy this parameter and all its upstream connections, recursively.
    Used with deferreds.
*/
void OutputParameter::copyWithUpstream()
{
    // TODO: implement
}

} // namespace NodeCore
