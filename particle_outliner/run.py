import pygame,numpy as np,sys
import variables
import simulation

pygame.init()

SW = variables.SW
SH = variables.SH
screen = pygame.display.set_mode((SW,SH))
pygame.display.set_caption("Outline Simulator")
#clock
clock = pygame.time.Clock()

#particle system
ps = simulation.ParticleSystem()

#Force field
force_field = simulation.ImpulseField(1)
ps.force_fields.append(force_field)
#font
font = pygame.font.SysFont("arial",15)



from image import img2,preprocessed

running = True
left_click = False; click = False
while running:
    #framerate
    clock.tick(160)

    screen.fill((255,255,255))

    pc_text = font.render("Particles : "+str(ps.particle_count), False, (0, 0, 0))
    fps_text = font.render("FPS : "+str(round(clock.get_fps(),2)),False,(0,0,0))

    screen.blit(pc_text,(0,0))
    screen.blit(fps_text,(variables.SW-fps_text.get_rect().width,0))
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            sys.exit(0)
        elif event.type == pygame.MOUSEBUTTONDOWN:
            click = True
            if event.button == 1: left_click = True
            else: left_click = False
        elif event.type == pygame.MOUSEBUTTONUP:
            click = False
    """
    for j in range(len(img2)):
        for i in range(len(img2[0])):
            if not img2[j][i]:
                pygame.draw.circle(screen,(0,0,0),(i+variables.offset_image,j+variables.offset_image),1)"""
    cursor = pygame.mouse.get_pos()
    if click:
        if left_click: ps.new_particle(cursor[0],cursor[1])
        else:
            force_field.point = cursor
            for p in ps.particles:
                force_field.update(p)

    #updating particles.
    ps.update(preprocessed)
    #drawing particles
    for p in ps.particles:
        pygame.draw.circle(screen,(0,0,0),(p.x,p.y),1)



    pygame.display.update()