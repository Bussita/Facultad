-module(tempo).
-export([wait/1, cronometro/3, empty_mailbox/0]).

wait(S) -> 
        receive
            after S -> ok
        end.

cronometro(Fun, Hasta, Periodo) ->
    if
        Hasta > Periodo ->
            wait(Periodo),                                    
            Fun(),
            cronometro(Fun, Hasta - Periodo, Periodo);
        Hasta < Periodo ->
            wait(Hasta),
            ok;
        true ->
            wait(Hasta),
            Fun(),
            ok
        end.

empty_mailbox() ->
            receive
                _Msg -> empty_mailbox()
            after 
                0 -> ok
            end.


