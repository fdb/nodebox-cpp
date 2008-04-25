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

#include "config.h"
#include "Transform.h"

#include "Utils.h"

namespace NodeCore {

Transform::Transform()
         :  m_transform(CGAffineTransformIdentity)
{
}

Transform::Transform(CGAffineTransform t)
         : m_transform(t)
{
}

bool Transform::isidentity() const
{
    return CGAffineTransformIsIdentity(m_transform);
}

void Transform::reset()
{
    m_transform = CGAffineTransformIdentity;
}

Transform &Transform::scale(float v)
{
    m_transform = CGAffineTransformScale(m_transform, v, v);
    return *this;
}

Transform &Transform::rotate(float v)
{
    m_transform = CGAffineTransformRotate(m_transform, radians(v));
    return *this;
}

Transform::operator CGAffineTransform() const
{
    return m_transform;
}

} // namespace NodeCore