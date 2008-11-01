from math import sin, cos, pi

background(None)
size(512, 512)

def circle(cx, cy, r):
    oval(cx-r/2, cy-r/2, r, r)
def square(cx, cy, r):
    rect(cx-r/2, cy-r/2, r, r)


font("DiavloBlack-Regular", 690)
pt = textpath("N", 0, 522)
inset = 6
pt.fit(inset+39, inset, WIDTH-inset*2, HEIGHT-inset*2)
#pt.draw()


for i in range(10000):
    x, y = random(WIDTH), random(HEIGHT)
    if pt.contains(x, y):
        sz = random(3.0, 8.0)
        fill(random(), 0, 0, random())
        stroke(random(), 0, 0, random())
        strokewidth(random(1.0, 5.0))
        rotate(random(360))
        fn  = choice((circle, square))
        fn(x, y, sz)
