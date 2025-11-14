CREATE DATABASE IF NOT EXISTS ajedrez_db;

USE ajedrez_db;

DROP TABLE IF EXISTS PARTIDAS;
DROP TABLE IF EXISTS JUGADORES;
DROP TABLE IF EXISTS CAMPEONATOS;

/*
Considerando la base de datos de los campeonatos internacionales de ajedrez, compuesta por
las siguientes relaciones:
    JUGADORES (J#, NOMBRE, NACIONALIDAD)
    CAMPEONATOS (C#, CNOMBRE, CATEGORIA)
    PARTIDAS (P#, J1#, J2#, C#, FECHA, RESULTADO)

*/

CREATE TABLE JUGADORES(
    `J#` VARCHAR(3) NOT NULL,
    NOMBRE VARCHAR(20) NOT NULL,
    NACIONALIDAD VARCHAR(10) NOT NULL,
    PRIMARY KEY (`J#`)
);

CREATE TABLE CAMPEONATOS(
    `C#` VARCHAR(3) NOT NULL,
    CNOMBRE VARCHAR(20) NOT NULL,
    CATEGORIA SMALLINT NOT NULL,
    PRIMARY KEY (`C#`)
);

CREATE TABLE PARTIDAS(
    `P#` VARCHAR(3) NOT NULL,
    `J1#` VARCHAR(3) NOT NULL,
    `J2#` VARCHAR(3) NOT NULL,
    `C#` VARCHAR(3) NOT NULL,
    FECHA DATE NOT NULL,
    RESULTADO VARCHAR(6) NOT NULL,
    PRIMARY KEY (`P#`),
    FOREIGN KEY (`J1#`) REFERENCES JUGADORES(`J#`) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (`J2#`) REFERENCES JUGADORES(`J#`) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (`C#`) REFERENCES CAMPEONATOS(`C#`) ON UPDATE CASCADE ON DELETE CASCADE
);

/* JUGADORES */
-- Argentinos
INSERT INTO JUGADORES VALUES ('J1', 'Carlos Pérez', 'Argentina');
INSERT INTO JUGADORES VALUES ('J2', 'María Gómez', 'Argentina');
INSERT INTO JUGADORES VALUES ('J3', 'Luis Torres', 'Argentina');

-- Brasileños
INSERT INTO JUGADORES VALUES ('J4', 'Paulo Silva', 'Brasil');
INSERT INTO JUGADORES VALUES ('J5', 'Ana Santos', 'Brasil');

-- Chilenos
INSERT INTO JUGADORES VALUES ('J6', 'Pedro Rojas', 'Chile');
INSERT INTO JUGADORES VALUES ('J7', 'Carmen Díaz', 'Chile');

-- Uruguayo
INSERT INTO JUGADORES VALUES ('J8', 'Diego Martín', 'Uruguay');

-- Jugador que nunca participó
INSERT INTO JUGADORES VALUES ('J9', 'Roberto Paz', 'Argentina');

/* CAMPEONATOS */
INSERT INTO CAMPEONATOS VALUES ('C1', 'Torneo FIDE', 1);
INSERT INTO CAMPEONATOS VALUES ('C2', 'Copa América', 2);
INSERT INTO CAMPEONATOS VALUES ('C3', 'Mundial Sub-20', 3);
INSERT INTO CAMPEONATOS VALUES ('C4', 'Olimpiada Chess', 1);
INSERT INTO CAMPEONATOS VALUES ('C5', 'Masters Buenos Aires', 2);
INSERT INTO CAMPEONATOS VALUES ('C6', 'Junior Cup', 4);  -- Categoría Junior (4)
INSERT INTO CAMPEONATOS VALUES ('C7', 'Elite Tournament', 1);

/* PARTIDAS */

-- Partidas en C1 (Torneo FIDE) - categoría 1
INSERT INTO PARTIDAS VALUES ('P1', 'J1', 'J4', 'C1', '2024-01-15', 'J1');     -- Carlos vs Paulo
INSERT INTO PARTIDAS VALUES ('P2', 'J2', 'J5', 'C1', '2024-01-16', 'EMPATE');  -- María vs Ana
INSERT INTO PARTIDAS VALUES ('P3', 'J6', 'J7', 'C1', '2024-01-17', 'J7');     -- Pedro vs Carmen (mismo país)

-- Partidas en C2 (Copa América) - categoría 2
INSERT INTO PARTIDAS VALUES ('P4', 'J1', 'J8', 'C2', '2024-02-10', 'J8');     -- Carlos vs Diego
INSERT INTO PARTIDAS VALUES ('P5', 'J4', 'J5', 'C2', '2024-02-11', 'J4');     -- Paulo vs Ana (mismo país)

-- Partidas en C6 (Junior Cup) - categoría Junior (4)
-- Argentinos en Junior
INSERT INTO PARTIDAS VALUES ('P6', 'J1', 'J2', 'C6', '2024-03-05', 'J1');     -- Carlos vs María (argentinos)
INSERT INTO PARTIDAS VALUES ('P7', 'J2', 'J3', 'C6', '2024-03-06', 'EMPATE'); -- María vs Luis (argentinos)
INSERT INTO PARTIDAS VALUES ('P8', 'J3', 'J4', 'C6', '2024-03-07', 'J3');     -- Luis vs Paulo

-- Partidas en C7 (Elite Tournament) - categoría 1
INSERT INTO PARTIDAS VALUES ('P9', 'J1', 'J6', 'C7', '2024-04-20', 'J1');     -- Carlos vs Pedro
INSERT INTO PARTIDAS VALUES ('P10', 'J2', 'J4', 'C7', '2024-04-21', 'J2');    -- María vs Paulo
INSERT INTO PARTIDAS VALUES ('P11', 'J8', 'J5', 'C7', '2024-04-22', 'J5');    -- Diego vs Ana

-- Más partidas en C1 y C7 para jugadores que participan en ambos
INSERT INTO PARTIDAS VALUES ('P12', 'J3', 'J8', 'C1', '2024-01-18', 'J3');    -- Luis en C1
INSERT INTO PARTIDAS VALUES ('P13', 'J3', 'J5', 'C7', '2024-04-23', 'EMPATE'); -- Luis en C7

-- Partidas adicionales en C3 (Mundial Sub-20)
INSERT INTO PARTIDAS VALUES ('P14', 'J6', 'J8', 'C3', '2024-05-10', 'J6');    -- Pedro vs Diego

/*
Dar soluciones en AR y en SQL a las siguientes consultas:

1) Obtener los códigos, las fechas y los resultados de las partidas en las que participaron
jugadores de Argentina en la categoría Junior(4).

SELECT `P#`, FECHA, RESULTADO
FROM PARTIDAS AS T1
WHERE EXISTS(
    SELECT `J#`
    FROM JUGADORES
    WHERE (`J#` = `J1#` OR `J#` = `J2#`) AND NACIONALIDAD = "Argentina"
)AND EXISTS(
    SELECT `C#`
    FROM CAMPEONATOS
    WHERE `C#` = T1.`C#` AND CATEGORIA = 4
);

2) Obtener los nombres de los jugadores que han participado en los campeonatos 'C1' o 'C7'.

SELECT NOMBRE
FROM JUGADORES AS T1
WHERE EXISTS(
    SELECT *
    FROM PARTIDAS
    WHERE (`J1#` = T1.`J#` OR `J2#` = T1.`J#`) AND (`C#` = "C1" OR `C#` = "C7")
);

3) Obtener los nombres de los jugadores que han participado en los campeonatos 'C1' y 'C7'.

SELECT NOMBRE
FROM JUGADORES AS T1
WHERE `J#` IN(
    SELECT `J1#` FROM PARTIDAS WHERE `C#` = "C1"
        UNION
    SELECT `J2#` FROM PARTIDAS WHERE `C#` = "C1"
)AND `J#` IN(
    SELECT `J1#` FROM PARTIDAS WHERE `C#` = "C7"
        UNION
    SELECT `J2#` FROM PARTIDAS WHERE `C#` = "C7"
);

4) Obtener los nombres de los campeonatos en que se enfrentaron jugadores de un mismo país.

*/
SELECT CNOMBRE
FROM CAMPEONATOS
WHERE `C#` IN(
    SELECT `C#`
    FROM PARTIDAS AS P
    WHERE (P.`J1#`,P.`J2#`) IN(
        SELECT `J1#`, `J2#`
        FROM JUGADORES AS T1, JUGADORES AS T2
        WHERE T1.NACIONALIDAD = T2.NACIONALIDAD
    )
);