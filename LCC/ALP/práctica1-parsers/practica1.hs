{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant bracket" #-}
import Parsing
import Control.Applicative
import Data.Char (isAlphaNum)
--Ejercicio 2
{-
Gramática:
expr -> term('+' expr | '-' expr | ε)
term -> factor('*' term | '/' term | ε)
factor -> number | '(' expr ')'
-}

data Expr = EInt Int | EOp Expr Ope Expr deriving Show
data Ope = Sum | Rest | Multi | Div deriving Show

expr :: Parser Expr
expr = do
        t <- term
        pSum t <|> pRest t <|> return t

term :: Parser Expr
term = do
        f <- factor
        pProd f<|> pDiv f <|> return f

factor :: Parser Expr
factor = do
            symbol "("
            e <- expr
            symbol ")"
            return e
        <|> do 
            x <- int
            return (EInt x)

pSum :: Expr -> Parser Expr
pSum t = do
        symbol "+"
        e <- expr
        return (EOp t Sum e)

pRest :: Expr -> Parser Expr
pRest t = do
        symbol "-"
        e <- expr
        return (EOp t Rest e)
pProd :: Expr -> Parser Expr
pProd t = do
        symbol "*"
        te <- term
        return (EOp t Multi te)

pDiv :: Expr -> Parser Expr
pDiv t = do
        symbol "/"
        te <- term
        return (EOp t Div te)
--Ejercicio 5

-- Ejercicio 6
data HType = HChar Char| HInt Int deriving Show
type HList = [HType]

hlist :: Parser HList
hlist = do
            symbol "["
            xs <- emptyCase <|> hlistContinue
            return xs
emptyCase :: Parser HList
emptyCase = do
            symbol "]"
            return []
hlistContinue :: Parser HList
hlistContinue = do
                    x <- htype
                    xs <- Parsing.many elementos
                    symbol "]"
                    return (x:xs)
htype :: Parser HType
htype =
        parChar <|> parInt

elementos :: Parser HType
elementos = do
                symbol ","
                htype

parChar :: Parser HType
parChar = do
            symbol "'"
            c <- letter
            symbol "'"
            return (HChar c)

parInt :: Parser HType 
parInt = do
            x <- int
            return (HInt x)
-- Ejercicio 7

data Hasktype = DInt | DChar | DFloat | Fun Hasktype Hasktype deriving Show

{-
ht -> type ( '->' ht | ε)
bt -> 'Int' | 'Char' | 'Float'
type -> bt | '(' ht ')'

ejemplo: Int -> Char -> Float
Fun DInt (Fun DChar DFloat)

(Int -> Char) -> Float
Fun (Fun DInt DChar) DFloat
-}


ht :: Parser Hasktype
ht = do 
        t1 <- typee
        htcontinue t1 <|> return t1 

htcontinue :: Hasktype -> Parser Hasktype
htcontinue t1= do
                symbol "->"
                t2 <- ht
                return (Fun t1 t2)


typee :: Parser Hasktype
typee = pbt <|> parenHt

pbt :: Parser Hasktype
pbt = pInt <|> pChar <|> pFloat

pInt :: Parser Hasktype
pInt = do
        t <- symbol "Int"
        return DInt

pChar :: Parser Hasktype
pChar = do
        t <- symbol "Char"
        return DChar

pFloat :: Parser Hasktype
pFloat = do
        t <- symbol "Float"
        return DFloat

parenHt :: Parser Hasktype
parenHt = do
            symbol "("
            t <- ht
            symbol ")"
            return t
--Ejercicio 8

{-
Gramática original

expr -> expr ('+' term | '-term') | term
term -> term ('*' factor | '/' factor) | factor
factor -> '(' expr ')'

Gramática equivalente sin recursión a izquierda

expr -> term expr'
expr' -> ('-' term | '+' term) expr' | term

queda hacer term'
-}
{-

data Expr = Num Int | BinOp Op Expr Expr
data Op = Add | Mul | Min | Div

-- hacer parser term
expr :: Parser Expr
expr = do   t <- term
            f <- expr'
            return (f t)

expr' :: Parser (Expr -> Expr)
expr' = pMin <|> pSum <|> pEmpty

pMin :: Parser (Expr -> Expr)
pMin = do   
        symbol "-"
        t <- term
        f <- expr'
        return (\e -> f (BinOp Min e t))

pSum :: Parser (Expr -> Expr)
pSum = do   
        symbol "+"
        t <- term
        f <- expr'
        return (\e -> f (BinOp Add e t))

pEmpty :: Parser (Expr -> Expr)
pEmpty = return id
-}

-- Ejercicio 9
{-

-}

data BasicTypes = BInt Int | BChar Char | BFloat Float