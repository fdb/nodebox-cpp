#ifndef Group_h
#define Group_h

#include <qdebug.h>

#include "grob.h"
#include "transform.h"

namespace NodeCore {

class Group : public Grob
{
public:
    Group();
    Group(const Group &group);
    virtual ~Group();
    
    Transform transform() const;
    void setTransform(const Transform& transform);
    
    void append(Grob *item);
    bool contains(Grob *item) const;
    int count() const;
    bool isEmpty() const;
    Grob *item(int index) const;
    void clear();
    
    virtual Rect bounds() const;

    virtual Grob* clone() const;

    virtual bool operator==(const Grob &g) const;
    virtual bool operator!=(const Grob &g) const;

private:
    QList<Grob*> m_items;
    Transform m_transform;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const Group &g);
#endif

} // namespace NodeCore

#endif // Group_h
