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
 
#include <NodeCore/BezierPath.h>
#include <NodeCore/Canvas.h>
#include <NodeCore/CanvasNode.h>
#include <NodeCore/Grob.h>
#include <NodeCore/Image.h>
#include <NodeCore/PathElement.h>
#include <NodeCore/Point.h>
#include <NodeCore/Rect.h>
#include <NodeCore/Transform.h>
#include <NodeCore/Utils.h>
#include <NodeCore/Exceptions.h>
#include <NodeCore/Connection.h>
#include <NodeCore/Field.h>
#include <NodeCore/Node.h>
#include <NodeCore/NodeInfo.h>
#include <NodeCore/NodeLibrary.h>
#include <NodeCore/NodeLibraryManager.h>
#include <NodeCore/posixutils.h>
#include <NodeCore/PythonNode.h>
