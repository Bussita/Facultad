-- Tiro Parabólico 3D - Modelos Físicos 2025
-- Trabajo Práctico - R321

module Main where

import System.IO
import Text.Printf
import System.Process (system)
import System.Exit (ExitCode)

-- Constante gravitatoria (m/s²)
g :: Double
g = 9.81

-- Tipo para vectores 3D
data Vec3 = Vec3 { vx :: Double, vy :: Double, vz :: Double }
    deriving (Show, Eq)

-- Operaciones vectoriales
(.+.) :: Vec3 -> Vec3 -> Vec3
(Vec3 x1 y1 z1) .+. (Vec3 x2 y2 z2) = Vec3 (x1+x2) (y1+y2) (z1+z2)

(.*.) :: Double -> Vec3 -> Vec3
k .*. (Vec3 x y z) = Vec3 (k*x) (k*y) (k*z)

-- Aceleración gravitatoria
gravedad :: Vec3
gravedad = Vec3 0 0 (-g)

-- Calcula la posición en el tiempo t dado r0, v0
-- Usando: r(t) = r0 + v0*t + (1/2)*a*t²
posicion :: Vec3 -> Vec3 -> Double -> Vec3
posicion r0 v0 t = r0 .+. (t .*. v0) .+. ((0.5 * t * t) .*. gravedad)

-- Calcula la velocidad en el tiempo t
-- Usando: v(t) = v0 + a*t
velocidad :: Vec3 -> Double -> Vec3
velocidad v0 t = v0 .+. (t .*. gravedad)

-- Genera una lista de puntos de la trayectoria desde t0=0 hasta tf
trayectoria :: Vec3 -> Vec3 -> Double -> Int -> [Vec3]
trayectoria r0 v0 tf numPuntos = 
    let dt = tf / fromIntegral (numPuntos - 1)
        tiempos = [dt * fromIntegral i | i <- [0..numPuntos-1]]
    in map (posicion r0 v0) tiempos

-- Guarda la trayectoria en un archivo para gnuplot
guardarTrayectoria :: FilePath -> [Vec3] -> IO ()
guardarTrayectoria archivo puntos = do
    writeFile archivo $ unlines $ map formatearPunto puntos
  where
    formatearPunto (Vec3 x y z) = printf "%.6f %.6f %.6f" x y z

-- Crea un script de gnuplot y lo ejecuta
graficarTrayectoria :: FilePath -> IO ()
graficarTrayectoria archivodatos = do
    let scriptGnuplot = unlines
            [ "set terminal qt persist"
            , "set title 'Trayectoria del Tiro Parabólico 3D'"
            , "set xlabel 'X (m)'"
            , "set ylabel 'Y (m)'"
            , "set zlabel 'Z (m)'"
            , "set grid"
            , "splot '" ++ archivodatos ++ "' using 1:2:3 with lines linewidth 2 title 'Trayectoria'"
            ]
    writeFile "plot_script.gp" scriptGnuplot
    putStrLn "\nGenerando gráfica con gnuplot..."
    putStrLn "(La ventana de gnuplot se mantendrá abierta, puedes cerrarla cuando quieras)"
    _ <- system "gnuplot plot_script.gp &"
    return ()

-- Función principal
main :: IO ()
main = do
    putStrLn "=== TIRO PARABÓLICO 3D ==="
    putStrLn "Modelos Físicos 2025 - R321\n"
    
    -- Entrada de datos: Posición inicial
    putStrLn "Ingrese la posición inicial (m):"
    putStr "  x0 = "
    hFlush stdout
    x0 <- readLn :: IO Double
    putStr "  y0 = "
    hFlush stdout
    y0 <- readLn :: IO Double
    putStr "  z0 = "
    hFlush stdout
    z0 <- readLn :: IO Double
    
    let r0 = Vec3 x0 y0 z0
    
    -- Entrada de datos: Velocidad inicial
    putStrLn "\nIngrese la velocidad inicial (m/s):"
    putStr "  vx0 = "
    hFlush stdout
    vx0 <- readLn :: IO Double
    putStr "  vy0 = "
    hFlush stdout
    vy0 <- readLn :: IO Double
    putStr "  vz0 = "
    hFlush stdout
    vz0 <- readLn :: IO Double
    
    let v0 = Vec3 vx0 vy0 vz0
    
    -- Entrada de datos: Tiempo
    putStrLn "\nIngrese el tiempo final (s):"
    putStr "  t = "
    hFlush stdout
    t <- readLn :: IO Double
    
    -- Calcular posición en el tiempo t
    let rt = posicion r0 v0 t
    let vt = velocidad v0 t
    
    -- Mostrar resultados
    putStrLn "\n=== RESULTADOS ==="
    printf "Posición inicial: r0 = (%.3f, %.3f, %.3f) m\n" x0 y0 z0
    printf "Velocidad inicial: v0 = (%.3f, %.3f, %.3f) m/s\n" vx0 vy0 vz0
    printf "Tiempo: t = %.3f s\n\n" t
    
    printf "Posición en t = %.3f s:\n" t
    printf "  x(%.3f) = %.6f m\n" t (vx rt)
    printf "  y(%.3f) = %.6f m\n" t (vy rt)
    printf "  z(%.3f) = %.6f m\n\n" t (vz rt)
    
    printf "Velocidad en t = %.3f s:\n" t
    printf "  vx(%.3f) = %.6f m/s\n" t (vx vt)
    printf "  vy(%.3f) = %.6f m/s\n" t (vy vt)
    printf "  vz(%.3f) = %.6f m/s\n\n" t (vz vt)
    
    -- Generar y guardar trayectoria
    let numPuntos = 500
    let traj = trayectoria r0 v0 t numPuntos
    
    guardarTrayectoria "trayectoria.dat" traj
    putStrLn "Trayectoria guardada en 'trayectoria.dat'"
    
    -- Preguntar si desea graficar
    putStr "\n¿Desea graficar la trayectoria? (s/n): "
    hFlush stdout
    respuesta <- getLine
    
    if respuesta `elem` ["s", "S", "si", "Si", "SI", "sí", "Sí"]
        then graficarTrayectoria "trayectoria.dat"
        else putStrLn "Gráfica omitida. Puede graficar manualmente con: gnuplot plot_script.gp"
    
    putStrLn "\n¡Programa finalizado!"