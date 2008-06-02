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

#import "CGColorHelper.h"

@implementation CGColorHelper

+ (CGColorSpaceRef)genericRGBSpace {
  static CGColorSpaceRef space = NULL;
  if(NULL == space) {
    space = CGColorSpaceCreateWithName (kCGColorSpaceGenericRGB);
  }
  return space;
}

+ (CGColorRef)clear
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.0f green:0.0f blue:0.0f alpha:0.0f];
  }
  return color;
}

+ (CGColorRef)white
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:1.0f green:1.0f blue:1.0f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)black
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.0f green:0.0f blue:0.0f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)gray
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.4f green:0.4f blue:0.4f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)lightGray
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.62f green:0.62f blue:0.62f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)veryLightGray
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.85f green:0.85f blue:0.85f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)red
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:1.0f green:0.0f blue:0.0f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)blue
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.0f green:0.0f blue:1.0f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)halfRed
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:1.0f green:0.0f blue:0.0f alpha:0.5f];
  }
  return color;
}  
+ (CGColorRef)halfBlue
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.0f green:0.0f blue:1.0f alpha:0.5f];
  }
  return color;
}

+ (CGColorRef)halfWhite
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:1.0f green:1.0f blue:1.0f alpha:0.5f];
  }
  return color;
}

+ (CGColorRef)connectionLineColor
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.3f green:0.3f blue:0.3f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)dragHighlightColor
{
  static CGColorRef color = NULL;
  if(color == NULL) {
    color = [self colorWithRed:0.0f green:0.0f blue:0.3f alpha:1.0f];
  }
  return color;
}

+ (CGColorRef)colorWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha
{
  CGFloat values[4] = {red, green, blue, alpha};
  return CGColorCreate([self genericRGBSpace], values);
}

@end
