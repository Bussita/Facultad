-- EJERCICIO 4
data Exp = Lit Int | Add Exp Exp | Sub Exp Exp | Prod Exp Exp | Div Exp Exp

eval :: Exp -> Int
eval (Lit n) = n
eval (Add e1 e2) = eval e1 + eval e2
eval (Sub e1 e2) = eval e1 - eval e2
eval (Prod e1 e2) = eval e1 * eval e2
eval (Div e1 e2) = div (eval e1)  (eval e2)

-- EJERCICIO 5 MALDITA NOTACION POLACA INVERSA

getFirst :: String -> (String, String)
getFirst s = aux "" (deleteSp s) where 
        deleteSp (' ':s) = s
        deleteSp s = s
        aux p "" = (reverse p, "")
        aux p (' ':s) = (reverse p,deleteSp s) 
        aux p ('+':s) = if p == [] then ("+", deleteSp s) else error "Expresion mal formada"
        aux p ('*':s) = if p == [] then ("*", deleteSp s) else error "Expresion mal formada"
        aux p ('-':s) = if p == [] then ("-", deleteSp s) else error "Expresion mal formada"
        aux p ('/':s) = if p == [] then ("/", deleteSp s) else error "Expresion mal formada"
        aux p (c:s) = aux (c:p) s
opTop :: (Exp -> Exp -> Exp) -> [Exp] -> String -> Exp

opTop op (x:y:p) s = parseS( op y x : p) s
opTop _ _ _ = error "Expresion mal formada"

parseS :: [Exp] -> String -> Exp
parseS p "" = if length p == 1 then head p else error "Expresion mal formada"
parseS p s = case x of
    "+" -> opTop Add p s'
    "-" -> opTop Sub p s'
    "*" -> opTop Prod p s'
    "/" -> opTop Div p s'
    n   -> parseS (Lit (read n) : p) s'
    where (x, s') = getFirst s

parseRPN :: String -> Exp
parseRPN s = parseS [] s

