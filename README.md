# FightingGameBuffer

Buffer circulaire:
On garde les input des X dernières frames, ça devient notre buffer
A chaque frame de la game loop, on check le buffer pour voir si il contient un move spécial

Les coups qui flush le buffer sont les coups spéciaux et supers