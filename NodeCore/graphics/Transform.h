#ifndef Transform_h
#define Transform_h

#include <ApplicationServices/ApplicationServices.h>

namespace NodeCore {

class Transform {
public:
    Transform();
    Transform(CGAffineTransform transform);
    Transform(const Transform &path);
    
    bool isidentity() const;
    void reset();

//    Transform& multiply(const Transform&);
    Transform& scale(float s); 
//    Transform& scale(double sx, double sy); 
//    Transform& scalenonuniform(double sx, double sy);
    Transform& rotate(float v);
//    Transform& rotateFromVector(double x, double y);
//    Transform& translate(double tx, double ty);
//    Transform& shear(double sx, double sy);
//    Transform& flipx();
//    Transform& flipy();
//    Transform& skew(double angleX, double angleY);
//    Transform& skewx(double angle);
//    Transform& skewy(double angle);

    operator CGAffineTransform() const;

private:
    CGAffineTransform m_transform;
};

} // namespace NodeCore

#endif // Transform_h
