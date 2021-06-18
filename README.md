# SimCity
Este proyecto plantea modelar una lógica simplificada del juego [SimCity de 1989](https://www.youtube.com/watch?v=A54blk-ojA4).
El SimCity es un juego de simulador de la vida y crecimiento de las ciudades.

- En nuestra versión del juego, las partidas comienzan con un mapa ya definido. Un mapa puede considerarse
una grilla infinita en cual corren rı́os. Los rı́os corren en lı́neas infinitas horizontales o verticales. En la
partida, en cada turno pueden agregarse casas o comercios. Cada uno ocupa una única casilla, que no
puede estar en el mismo lugar que un rı́o ni encima de otra construcción.
- Los comercios y casas además tienen un nivel de avance. En las casas, el nivel se define como la cantidad
de turnos que sucedieron desde que fue agregada. En los comercios, el nivel se define de igual manera, con
la excepción de que si una o más casas a 3 casilleros de distancia manhattan 4 tiene un nivel más alto, el
comercio adopta el máximo de ellos.
- El juego se sucede por turnos, donde en cada uno se debe agregar al menos una construcción, pudiéndose
agregar más de una en el mismo turno.
-Partidas colaborativas: dos partidas de SimCity se pueden unirse en una nueva. Esta acción deberá hace concoordar los rios y construcciones de ambas ciudades. Para que el mecanismo de unión sea constructivo y no destructivo, se restringio la posibilidad de unir dos SimCitys a los casos donde no se solapen rı́os con construcciones. Además,
para evitar la depresión de quienes juegan, tampoco se solapan las construcciones de nivel máximo de
cualquiera de las partidas con otras construcciones.
