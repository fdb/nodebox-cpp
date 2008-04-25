#include "NodeCore.h"

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