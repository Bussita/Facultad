{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant lambda" #-}
{-# OPTIONS_GHC -Wno-noncanonical-monad-instances #-}
{-# HLINT ignore "Redundant bracket" #-}
import System.IO
import GHC.IO.Handle (hSetBuffering)
import Text.Read 
--Ejercicio 2
getChars :: Int -> IO String
getChars n = sequenceA (replicate n getChar)

--Ejercicio 3
guessTheNumber :: Int -> IO ()
guessTheNumber n = do
            xs <- getLine

            case readMaybe xs :: Maybe Int of
                Just m -> if m == n then
                            putStr "Adivinaste! Juego terminado.\n"
                            else
                            do
                                putStr "Erroneo! Intente denuevo.\n"
                                guessTheNumber n
                Nothing -> do
                    putStr "Lo que ingresaste no es un número!!!\n"
                    guessTheNumber n

-- Se puede hacer una funcion "print board" que le pases una [[Bool]]
-- si es true printea la estrella, si es false no.

-- Luego en nim game solo agarras y preguntas cantidad / cuales estrellas sacar.
nimGame :: IO ()
nimGame = do
            putStr "Tablero: "
            putStr "1: ***** \n 2:**** \n 3: *** \n 4: ** \n 5* \n"

-- Ejercicio 6

newtype State s a = St {runState :: s -> (a, s)}

instance Monad (State s) where
    return x = St (\s -> (x , s))
    (St h) >>= f = St (\s -> let (x , s') = h s
                            in runState (f x ) s')

set :: s -> State s ()
set s = St (\_ -> ((), s))

getS :: State s s
getS = St (\s -> (s, s))

--Ejercicio 8

data T = Con Int | Div T T

newtype M s e a = M {runM :: s -> Either e (a,s)}

instance Functor (M s e) where
    fmap f (M h) = M $ \s ->
        case h s of
            Left e -> Left e
            Right (a, s') -> Right (f a, s')

instance Applicative (M s e) where
    pure x = M $ \s -> Right (x, s)
    (M hf) <*> (M ha) = M $ \s ->
        case hf s of
            Left e -> Left e
            Right (f, s') ->
                case ha s' of
                    Left e -> Left e
                    Right (a, s'') ->
                        Right (f a, s'')

instance Monad (M s e) where
    return :: a -> M s e a
    return x = M (\s -> Right (x,s))
    (>>=) :: M s e a -> (a -> M s e b) -> M s e b
    M h >>= f = M (\s -> case h s of
                                Right (a,s') -> runM (f a) s'
                                Left e -> Left e)


eval :: T -> M Int String Int
eval (Con n) = return n
eval (Div t1 t2) = do 
                    v1 <- eval t1
                    v2 <- eval t2
                    if v2 == 0 then raise "Error: Division por cero."
                    else do
                            modify (+1)
                            return (v1 `div` v2)

raise :: String -> M Int String Int
raise s = M (\_ -> Left s)

modify :: (Int -> Int) -> M Int String ()
modify f = M (\s -> Right ((), f s))

doEval :: T -> Either String (Int, Int)
doEval t = runM (eval t) 0

eval' :: T -> M Int String Int
eval' (Con n) = return n
eval' (Div t1 t2) = eval t1 >>= \v1 ->
                        eval t2 >>= \v2 ->
                            if v2 == 0 then raise "Error: Division por cero." else modify (+1) >> return (v1 `div` v2)

-- Ejercicio 9

data Mo m a = Mk (m (Maybe a))
-- item a (falta prueba)
instance Monad (Mo m) where
    return x = Mk (return (Just x))
    Mk mma >>= f = Mk $ do
                            ma <- mma
                            case ma of
                                Just x -> runm (f x)
                                Nothing -> return Nothing

runMk :: Mo m a -> m (Maybe a)
runMk (Mk x) = x
-- item b
throw :: Monad m => Mo m a
throw = Mk (return Nothing)

data StInt a = Sti (Int -> (a, Int))

type N a = Mo StInt a

runStInt :: StInt a -> Int -> (a, Int)
runStInt (Sti x) = x

-- item c

get :: N Int
get = Mk (Sti (\i -> (Just i, i)))

put :: Int -> N ()
put n = Mk (Sti (\_ -> (Just (), n)))

main :: IO ()
main = do
        -- Ejercicio 1: Hola mundo en pantalla.
        putStr "Hola mundo!\n"
        
        {- Ejercicio 2
        hSetBuffering stdin NoBuffering
        xs <- getChars 5
        putStr ("\nLista: " ++ xs ++ "\n cantidad: " ++ show (length xs) ++ "\n")
        -}

        -- Ejercicio 3
        {-
        putStr "Comienza el juego! Adivine el numero secreto.\n"
        guessTheNumber 5
        -}

        --Ejercicio 4
        -- nimGame

        --Ejercicio 8
