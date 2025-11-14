-module(min).
-export([min/1]).

min([Hd]) -> Hd;
min([Hd|T1]) -> 
    Rest = min(T1),
    if
        Hd < Rest -> Hd;
        true -> Rest
    end.