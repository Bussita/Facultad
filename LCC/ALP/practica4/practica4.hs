{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE TypeApplications #-}
{-# LANGUAGE ImpredicativeTypes #-}
{-# LANGUAGE ScopedTypeVariables #-}

double :: forall x . (x -> x) -> x -> x
double = \f -> \x -> f(f x)

doubleNat :: (Int -> Int) -> Int -> Int
doubleNat = double @Int

doubleFun :: ((Int -> Int) -> Int -> Int) -> (Int -> Int) -> Int -> Int
doubleFun = double @(Int->Int)

id' :: forall x . x->x
id' = \x->x

--item b

quadruple :: forall x . (x -> x) -> x -> x
quadruple f x = double (double f) x


type CBool = forall x . x -> x -> x

cfalse :: CBool
cfalse = \p -> \q -> q

ctrue :: CBool
ctrue = \p -> \q -> p

cand :: CBool -> CBool -> CBool
cand = \p -> \q -> p @CBool q cfalse

checkBool :: CBool -> Bool
checkBool b = b True False