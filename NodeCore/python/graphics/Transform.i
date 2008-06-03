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

};

} // namespace NodeCore
