from z3 import *

x = Real('x')
y = Real('y')
z = Real('z')
dx = Real('dx')
dy = Real('dy')
dz = Real('dz')
s = Solver()
n = 300

for i in range(n):
    [l1,l2] = input().split('@')
    xp,yp,zp = map(int,l1.split(','))
    dxp,dyp,dzp = map(int,l2.split(','))
    t = Real('t'+str(i))
    s.add(x+dx*t == xp+dxp*t)
    s.add(y+dy*t == yp+dyp*t)
    s.add(z+dz*t == zp+dzp*t)
    s.add(t>=0)

print(s.check())
print(s.model().eval(x+y+z))