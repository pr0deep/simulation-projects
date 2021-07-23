import numpy as np, random
import variables

def isStable(img,point):
    """
    for j in range(len(img)):
        for i in range(len(img[0])):
            if not img[j][i]:
                if int(point[0])==i+variables.offset_image and int(point[1])==j+variables.offset_image:return True
    return False"""

    for i in range(len(img)):
        if img[i] == (int(point[0]),int(point[1])):return True
    return False
class Particle:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.vx = random.choice([-1, 1]) * np.random.rand()
        self.vy = random.choice([-1, 1]) * np.random.rand()
        self.mass = 1;self.stable = False

    def update_pos(self):
        if self.stable:
            if self.vx !=0 or self.vy !=0:
                self.stable = False
        if variables.SW > self.x + self.vx > 0:
            self.x += self.vx
        else:
            self.vx *= -1
        if variables.SH > self.y + self.vy > 0:
            self.y += self.vy
        else:
            self.vy *= -1


class ParticleSystem:
    def __init__(self):
        self.particles = []
        self.particle_count = 0
        self.force_fields = []

    def update(self,img):
        for p in self.particles:
            p.update_pos()
            if p.stable or isStable(img,(p.x,p.y)):
                p.vx = 0;p.vy = 0
                p.stable = True;

    def new_particle(self,x,y):
        self.particle_count += 1
        self.particles.append(Particle(x, y))

class Field:
    def __init__(self,s):
        self.strength = s

    def update(self,particle):
        if variables.SW > particle.x + self.strength > 0:
            particle.vx += self.strength
        else:
            particle.vx *= -1
        if variables.SH > particle.vy + particle.vy > 0:
            particle.vy += self.strength
        else:
            particle.vy *= -1

class ImpulseField(Field):
    def __init__(self,s):
        super().__init__(s)
        self.point = (0,0)

    def update(self,particle):
        r2 = np.square((self.point[1]-particle.y)/variables.SH)+np.square((self.point[0]-particle.x)/variables.SW)+1
        theta = np.arctan((self.point[1]-particle.y)/(self.point[0]-particle.x))
        cos_theta = np.cos(theta);sin_theta = np.sin(theta)

        particle.vx += cos_theta*self.strength/r2
        particle.vy += sin_theta*self.strength/r2

