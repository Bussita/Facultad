-module(macros).
-export([test/0]).

-ifndef(DEBUG).
    -define(DBG(Str, Args), io:format(Str, Args)).
-else
    -define(DBG(Str,Args),ok).
-endif

test() ->
    ?DBG("Esto es un ~p ~n",[test]),
    ok.
