/*
1. Mostrar las ciudades y su correspondiente pais, desde las cuales
llegan vuelos al aeropuerto de Rosario, Argentina.
*/
SELECT Ciudad, Pais
FROM AEROPUERTO
WHERE CodigoAeropuerto IN(
    SELECT CodAeropOrigen
    FROM VUELO
    WHERE CodAeropDestino = "ROS"
);

/*
2. Encontrar el codigo de vuelo y horario de salida de los vuelos
internos de todos los paises (un vuelo es interno cuando sale
de un aeropuerto ubicado en un pais y llega a otro aeropuerto
ubicado en el mismo pais)
*/
SELECT CodVuelo, HoraSalida
FROM VUELO AS T
WHERE (CodAeropOrigen, CodAeropDestino) IN(
    SELECT T1.CodigoAeropuerto, T2.CodigoAeropuerto
    FROM AEROPUERTO AS T1, AEROPUERTO AS T2
    WHERE T1.PAIS = T2.PAIS AND T1.CodigoAeropuerto<>T2.CodigoAeropuerto
);

/*
3.Para cada pais, obtener el nombre del pais y la cantidad de companias (ubicadas en ese pais)
 que tienen mas de 10 vuelos al extranjero. 
*/
SELECT PAIS, COUNT(COMPANIA)
FROM PILOTO AS T1
WHERE EXISTS(
    SELECT 1
    FROM ASIGNACION-VIAJE AS T2
    WHERE T2.CodPiloto = T1.CodPiloto AND EXISTS(
        SELECT 1
        FROM VUELO as T3
        WHERE T3.CodVuelo = T2.CodVuelo AND EXISTS(
            SELECT 1
            FROM AEROPUERTO AS T4
            WHERE (CodAeropuerto = T3.CodAeropDestino OR CodAeropuerto = T3.CodAeropOrigen) AND T4.PAIS <> T1.PAIS
        )
    )
)
GROUP BY PAIS
HAVING COUNT(COMPANIA) > 10