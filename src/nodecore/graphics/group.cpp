#include "group.h"

namespace NodeCore {
    
Group::Group()
     : Grob()
{
}

Group::Group(const Group &group)
     : Grob()
{
    Grob *item;
    foreach (item, group.m_items) {
        append(item->clone());
    }
}

Group::~Group()
{
    Grob *item;
    foreach (item, m_items) {
        delete item;
    }
}


Transform Group::transform() const
{
    return m_transform;
}

void Group::setTransform(const Transform& transform)
{
    m_transform = transform;
}

void Group::append(Grob *item)
{
    m_items.append(item);
}

bool Group::contains(Grob *item) const
{
    return m_items.contains(item);
}

int Group::count() const
{
    return m_items.count();
}

bool Group::isEmpty() const
{
    return m_items.isEmpty();
}

Grob *Group::item(int index) const
{
    return m_items.at(index);
}

void Group::clear()
{
    m_items.clear();
}

Rect Group::bounds() const
{
    if (isEmpty()) return Rect();
    Rect r;
    bool first;
    Grob *item;
    foreach (item, m_items) {
        if (first) {
            r = item->bounds();
            first = false;
        } else {
            r.unite(item->bounds());
        }
    }
    return r;
}

Grob* Group::clone() const
{
    return new Group(*this);
}

bool Group::operator==(const Grob &g) const
{
    if (this == &g) return true;
    const Group &other = dynamic_cast<const Group&>(g);
    if (count() != other.count()) return false;
    for (int i=0; i<count(); i++) {
        if (item(i) != other.item(i))
            return false;
    }
    return true;
}

bool Group::operator!=(const Grob &g) const
{
    return !operator==(g);
}

} // namespace NodeCore
