CREATE DATABASE IF NOT EXISTS practicaAvanzada_db;

USE practicaAvanzada_db;
/*
Considerando la base de datos compuesta por las siguientes relaciones:
    COMPETICION (P#, DESCRIPCION, CATEGORIA)
    CLUB (C#, NOM_C, PRESUPUESTO)
    PARTICIPACION (C#, P#, PUESTO)
*/

DROP TABLE IF EXISTS COMPETICION;
DROP TABLE IF EXISTS CLUB;
DROP TABLE IF EXISTS PARTICIPACION;

CREATE TABLE COMPETICION (
    `P#` VARCHAR(3) NOT NULL,
    DESCRIPCION VARCHAR(100),
    CATEGORIA INT NOT NULL,
    PRIMARY KEY (`P#`)
);

CREATE TABLE CLUB (
    `C#` VARCHAR(3) NOT NULL,
    NOM_C VARCHAR(20),
    PRESUPUESTO DECIMAL NOT NULL,
    PRIMARY KEY (`C#`)
);

CREATE TABLE PARTICIPACION(
    `C#` VARCHAR(3) NOT NULL,
    `P#` VARCHAR(3) NOT NULL,
    PUESTO SMALLINT NOT NULL,
    PRIMARY KEY (`C#`,`P#`),
    FOREIGN KEY (`C#`) REFERENCES CLUB(`C#`) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (`P#`) REFERENCES COMPETICION(`P#`) ON DELETE CASCADE ON UPDATE CASCADE
);

/* COMPETICIONES */
INSERT INTO COMPETICION VALUES ('P1', 'Copa Nacional', 2);
INSERT INTO COMPETICION VALUES ('P2', 'Torneo Regional', 2);
INSERT INTO COMPETICION VALUES ('P3', 'Liga Premier', 1);
INSERT INTO COMPETICION VALUES ('P4', 'Copa Libertadores', 3);
INSERT INTO COMPETICION VALUES ('P5', 'Sudamericana', 2);

/* CLUBES */
INSERT INTO CLUB VALUES ('C1', 'River Plate', 8000000);
INSERT INTO CLUB VALUES ('C2', 'Boca Juniors', 7500000);
INSERT INTO CLUB VALUES ('C3', 'Racing Club', 4000000);
INSERT INTO CLUB VALUES ('C4', 'Independiente', 6000000);
INSERT INTO CLUB VALUES ('C5', 'San Lorenzo', 3500000);

/* PARTICIPACIONES */
-- River (C1): participó en P1, P2, P3, P4, P5 (todas) y ganó P1, P3
INSERT INTO PARTICIPACION VALUES ('C1', 'P1', 1);  -- 1er puesto en P1
INSERT INTO PARTICIPACION VALUES ('C1', 'P2', 2);  -- 2do puesto en P2
INSERT INTO PARTICIPACION VALUES ('C1', 'P3', 1);  -- 1er puesto en P3
INSERT INTO PARTICIPACION VALUES ('C1', 'P4', 3);  -- 3er puesto en P4
INSERT INTO PARTICIPACION VALUES ('C1', 'P5', 2);  -- 2do puesto en P5

-- Boca (C2): participó en P1, P2 (ambas de categoría 2) y ganó P2
INSERT INTO PARTICIPACION VALUES ('C2', 'P1', 3);  -- 3er puesto en P1
INSERT INTO PARTICIPACION VALUES ('C2', 'P2', 1);  -- 1er puesto en P2

-- Racing (C3): participó en P3, P4, nunca ganó
INSERT INTO PARTICIPACION VALUES ('C3', 'P3', 4);  -- 4to puesto
INSERT INTO PARTICIPACION VALUES ('C3', 'P4', 5);  -- 5to puesto

-- Independiente (C4): participó en P1, P2 y ganó solo P4
INSERT INTO PARTICIPACION VALUES ('C4', 'P1', 2);  -- 2do puesto
INSERT INTO PARTICIPACION VALUES ('C4', 'P2', 4);  -- 4to puesto
INSERT INTO PARTICIPACION VALUES ('C4', 'P4', 1);  -- 1er puesto en P4

-- San Lorenzo (C5): participó en P5, nunca ganó
INSERT INTO PARTICIPACION VALUES ('C5', 'P5', 3);  -- 3er puesto


/*
Dar soluciones en AR y en SQL a las siguientes consultas:

a) Obtener los nombres de los clubes con presupuesto mayor que 5 millones y que hayan
participado en competiciones de categoría igual a 2.

SELECT NOM_C
FROM CLUB AS T1
WHERE T1.`C#` IN
(SELECT `C#` FROM PARTICIPACION WHERE `P#` IN (SELECT `P#` FROM COMPETICION WHERE CATEGORIA = 2) AND T1.PRESUPUESTO > 5000000); 


b) Obtener los nombres de los clubes que sólo han conseguido el primer puesto.

SELECT NOM_C FROM CLUB
WHERE `C#` IN (
    SELECT `C#` 
    FROM PARTICIPACION 
    GROUP BY `C#` 
    HAVING MAX(PUESTO) = 1 AND MIN(PUESTO) = 1
);

c) Obtener los nombres de los clubes que han participado en todas las competiciones.

SELECT NOM_C
FROM CLUB
WHERE `C#` IN(
    SELECT `C#`
    FROM PARTICIPACION AS T
    WHERE NOT EXISTS(
        SELECT `P#`
        FROM COMPETICION AS T2
        WHERE T2.`P#` NOT IN (SELECT `P#` FROM PARTICIPACION AS T3 WHERE T3.`C#` = T.`C#`)
    )
);

d) Obtener los nombres de los clubes que participaron en las competiciones P1 y P2 (en ambas).

SELECT NOM_C
FROM CLUB
WHERE `C#` IN(
    SELECT `C#`
    FROM PARTICIPACION AS T
    WHERE `P#` = "P1" AND EXISTS(
        SELECT *
        FROM PARTICIPACION AS T2
        WHERE T2.`C#` = T.`C#` AND T2.`P#` = "P2"
    )
);

e) Obtener el nombre y presupuesto de los clubes que no han conseguido un primer puesto.
comentario: se puede hacer con NOT IN y sin hacer GROUP BY, considerando solamente WHERE PUESTO = 1, y eso incluye
a aquellos clubes que no han participado inclusive

SELECT NOM_C, PRESUPUESTO
FROM CLUB
WHERE `C#` IN(
    SELECT `C#`
    FROM PARTICIPACION
    GROUP BY `C#`
    HAVING MIN(PUESTO)>=2
); 
*/