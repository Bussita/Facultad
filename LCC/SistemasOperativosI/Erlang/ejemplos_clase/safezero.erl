-module(safezero).
-export([safezero/2,test/0]).

safezero(M,N) ->
    case catch (M / N) of
        {'EXIT',{badarith, Args}} -> io:format("Division por cero. Traza ~p ~n",[Args]);
        Res -> Res
    end.

test() ->
    safezero(6,2),
    safezero(6,0),
    ok.
