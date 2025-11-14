/*
Escribir en AR y en SQL las sentencias necesarias para responder a las preguntas siguientes:

a) Videoclubes que disponen de alguna película que le guste al aficionado José Pérez.

SELECT VIDEOCLUB
FROM VIDEOTECA
WHERE `P#` IN(
    SELECT `P#`
    FROM GUSTA
    WHERE AFICIONADO = "José Perez"
);

b) Aficionados que son socios al menos de un videoclub que dispone de alguna película de su
gusto.

SELECT AFICIONADO
FROM SOCIO AS T1
WHERE EXISTS(
    SELECT *
    FROM GUSTA
    WHERE GUSTA.AFICIONADO = T1.AFINICIONADO
    AND GUSTA.PELICULA IN(
        SELECT PELICULA
        FROM VIDEOTECA
        WHERE VIDEOCLUB = T1.VIDEOCLUB
    )
);

c) Aficionados que no son socios de ningún videoclub donde tengan alguna película de su gusto.

SELECT AFICIONADO
FROM SOCIO AS T1
WHERE NOT EXISTS(
    SELECT *
    FROM GUSTA
    WHERE GUSTA.AFICIONADO = T1.AFICIONADO
    AND GUSTA.PELICULA IN(
        SELECT PELICULA
        FROM VIDEOTECA
        WHERE VIDEOCLUB = T1.VIDEOCLUB
    )
);

d) Videoclubes que disponen tanto de la película A como de la película B (ambas).

SELECT VIDEOCLUB
FROM VIDEOTECA AS T1
WHERE T1.PELICULA = "A"
AND EXISTS(
    SELECT 1
    FROM VIDEOTECA AS T2
    WHERE T2.VIDEOCLUB = T1.VIDEOCLUB AND T2.PELICULA = "B"
);

e) Aficionados que son socios de al menos dos videoclubes que tengan alguna película de su
gusto.
*/