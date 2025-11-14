/*
Reuniones:

6) Obtener todas las 3-uplas número de proveedor/número de parte/ número de proyecto tales que el
proveedor, la parte y el proyecto indicados estén todos en la misma ciudad (cosituados).


SELECT SPJ.`S#`, SPJ.`P#`, SPJ.`J#` FROM SPJ, S, P, J WHERE 
S.CIUDAD = P.CIUDAD AND S.CIUDAD = J.CIUDAD AND SPJ.`S#` = S.`S#`
AND SPJ.`P#` = P.`P#` AND SPJ.`J#` = J.`J#`

7) Obtener todas las 3-uplas número de proveedor/número de parte/ número de proyecto tales que el
proveedor, la parte y el proyecto indicados no estén todos cosituados.


SELECT SPJ.`S#`, SPJ.`P#`, SPJ.`J#` 
FROM SPJ, S, P, J 
WHERE (S.CIUDAD <> P.CIUDAD OR S.CIUDAD <> J.CIUDAD <> P.CIUDAD <> J.CIUDAD) 
AND SPJ.`S#` = S.`S#` AND SPJ.`P#` = P.`P#` AND SPJ.`J#` = J.`J#`

8) Obtener todas las 3-uplas número de proveedor/número de parte/ número de proyecto tales que el
proveedor, la parte y el proyecto indicados estén todos en diferente ciudad.

SELECT SPJ.`S#`, SPJ.`P#`, SPJ.`J#` 
FROM SPJ, S, P, J 
WHERE S.CIUDAD <> P.CIUDAD AND S.CIUDAD <> J.CIUDAD AND J.CIUDAD <> P.CIUDAD AND SPJ.`S#` = S.`S#`
AND SPJ.`P#` = P.`P#` AND SPJ.`J#` = J.`J#`

9) Obtener los números de las partes suministradas por algún proveedor de Londres.

SELECT DISTINCT `P#`, SS.CIUDAD AS "ciudad proveedor" FROM SPJ, S AS SS WHERE SS.CIUDAD = 'Londres' AND SPJ.`S#` = SS.`S#`;

10) Obtener los números de las partes suministradas por un proveedor de Londres a un proyecto en
Londres.

SELECT DISTINCT SPJ.`S#`,`P#`,SPJ.`J#` FROM SPJ, S AS SS, J AS JJ 
WHERE SPJ.`S#` = SS.`S#` AND SPJ.`J#` = JJ.`J#` 
AND JJ.CIUDAD = 'Londres' AND SS.CIUDAD = 'Londres'

11) Obtener todas las parejas de nombres de ciudad tales que un proveedor de la primera ciudad
suministre partes a un proyecto en la segunda ciudad.

SELECT DISTINCT S.CIUDAD, J.CIUDAD
FROM SPJ, S, J WHERE SPJ.`S#` = S.`S#` AND SPJ.`J#` = J.`J#`

12) Obtener los números de las partes suministradas a un proyecto por un proveedor situado en la misma
ciudad que el proyecto.

SELECT DISTINCT `P#`
FROM SPJ, S, J WHERE SPJ.`S#` = S.`S#` AND SPJ.`J#` = J.`J#`
AND S.CIUDAD = J.CIUDAD

13) Obtener los números de los proyectos a los cuales suministra partes por lo menos un proveedor
situado en una ciudad distinta.

SELECT DISTINCT SPJ.`J#` FROM SPJ, S, J WHERE S.`S#` = SPJ.`S#`
AND J.`J#` = SPJ.`J#` AND S.CIUDAD <> J.CIUDAD

14) Obtener todas las parejas de números de parte tales que algún proveedor suministre las dos partes
indicadas.

SELECT DISTINCT SPJ.`P#`, SPJAUX.`P#` FROM SPJ, SPJ AS SPJAUX WHERE
SPJ.`S#` = SPJAUX.`S#` AND SPJ.`P#` < SPJAUX.`P#`

Funciones de agregados:

15) Obtener el número total de proyectos a los cuales suministra partes el proveedor S1.

SELECT COUNT(*) FROM SPJ WHERE `S#` = 'S1';

16) Obtener la cantidad total de la parte Pl suministrada por el proveedor Sl.

SELECT SUM(CANTIDAD) FROM SPJ WHERE `S#` = 'S1' AND `P#` = 'P1';

17) Para cada parte suministrada a un proyecto, obtener el número de parte, el número de proyecto y la
cantidad total correspondiente.

SELECT `P#`, SUM(CANTIDAD) FROM SPJ GROUP BY `P#`;

18) Obtener los números de las partes suministradas a algún proyecto tales que la cantidad promedio
suministrada sea mayor que 320.

SELECT `P#`, AVG(CANTIDAD)
FROM SPJ
GROUP BY `P#`
HAVING AVG(CANTIDAD) > 320

Diversas:

19) Obtener todos los envios para los que la cantidad no sea nula.

SELECT * FROM SPJ WHERE CANTIDAD IS NOT NULL OR CANTIDAD <> 0

20) Obtener números de proyecto y ciudades en los cuales la segunda letra
del nombre de la ciudad sea una "o".

SELECT `J#`, CIUDAD FROM J WHERE CIUDAD LIKE "_o%" OR CIUDAD LIKE "_O%"

Subconsultas:

21) Obtener los nombres de los proyectos a los cuales suministra partes el proveedor S1.

SELECT JNOMBRE
FROM J
WHERE `J#` IN 
(SELECT `J#` FROM SPJ WHERE `S#` = "S1"); 

22) Obtener los colores de las partes suministradas por el proveedor S1.

SELECT COLOR
FROM P
WHERE `P#` IN
(SELECT `P#` FROM SPJ WHERE `S#` = "S1");

23) Obtener los números de las partes suministradas a cualquier proyecto en Londres

SELECT `P#`
FROM P
WHERE `P#` IN
(SELECT `P#` FROM SPJ WHERE `J#` IN
(SELECT `J#` FROM J WHERE CIUDAD = "Londres"));


24) Obtener los números de los proyectos donde se utilice al menos una de las partes suministradas por el
proveedor S1.

SELECT DISTINCT `J#` FROM SPJ WHERE `P#` IN (SELECT `P#` FROM SPJ WHERE `S#` = "S1");

25) Obtener los números de los proveedores que suministren por lo menos una de las partes
suministradas por al menos uno de los proveedores que suministran por lo menos una parte roja.

SELECT `S#`
FROM SPJ
WHERE `P#` IN
(SELECT `P#` FROM SPJ WHERE `S#` IN 
(SELECT `S#` FROM SPJ WHERE `P#` IN 
(SELECT `P#` FROM P WHERE COLOR = "Rojo")));

26) Obtener los números de los proveedores cuya situación sea inferior a la del proveedor S1.

SELECT `S#` FROM S, (SELECT SITUACION FROM S WHERE `S#` = "S1") AS S1SIT
WHERE S.SITUACION < S1SIT.SITUACION;

27) Obtener los números de los proyectos cuya ciudad sea la primera en la lista alfabética de las ciudades
donde hay proyectos.

SELECT `J#`
FROM J
WHERE CIUDAD = (SELECT MIN(CIUDAD) FROM J);

28) Repetir el ejercicio 23 utilizando EXISTS en la solución.

SELECT DISTINCT `P#` 
FROM SPJ 
WHERE EXISTS (SELECT `J#` FROM J WHERE SPJ.`J#` = J.`J#` AND J.CIUDAD = "Londres");

29) Repetir el ejercicio 24 utilizando EXISTS en la solución.

SELECT DISTINCT `J#`
FROM SPJ AS T1
WHERE EXISTS (SELECT `P#` FROM SPJ WHERE `S#` = "S1" AND `P#` = T1.`P#`);

30) Obtener los números de los proyectos a los cuales no suministra ninguna parte roja ninguno de los
proveedores de Londres.

SELECT DISTINCT `J#`
FROM SPJ AS T1
WHERE NOT EXISTS 
(SELECT `S#`,`P#` FROM SPJ WHERE 
EXISTS (SELECT `P#` FROM P WHERE COLOR = "Rojo" AND P.`P#` = T1.`P#`) 
AND EXISTS (SELECT `S#` FROM S WHERE CIUDAD = "Londres") AND `S#`=T1.`S#`); 

31) Obtener los números de los proyectos para los cuales S1 es el único proveedor.

SELECT `J#`
FROM SPJ AS T1
WHERE EXISTS (SELECT `S#` FROM SPJ WHERE `S#` = "S1" AND `J#` = T1.`J#`)
AND NOT EXISTS (SELECT `S#` FROM SPJ WHERE `S#` <> "S1" AND `J#` = T1.`J#`);

Union: 
32) Construir una lista ordenada de todas las ciudades en las cuales esté situado por lo menos un
proveedor, una parte o un proyecto.

Operaciones de actualizacion:

33) Cambiar a gris el color de todas las partes rojas.

UPDATE P SET COLOR = "Gris" WHERE COLOR = "Rojo";

34) Eliminar todos los proyectos para los cuales no haya envíos.

DELETE FROM J WHERE `J#` NOT IN (SELECT `J#` FROM SPJ); 

35) Insertar un nuevo proveedor (S10) en la tabla S. El nombre y la ciudad son Salazar y Nueva York,
respectivamente; la situación no se conoce todavía.

INSERT INTO S(`S#`,SNOMBRE, CIUDAD) VALUES ("S10", "Salazar", "Nueva York");
*/