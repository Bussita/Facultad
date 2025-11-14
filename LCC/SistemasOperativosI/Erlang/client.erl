-module(client).

-define(Puerto, 1234).
-define (Dir, "localhost").
-export([cliente/0]).
cliente() ->
    case gen_tcp:connect(?Dir,?Puerto , [binary, {active, false}]) of
        {ok, Socket} ->
            {ok, Str} = io:fread("Enviar:", "~s"),
            gen_tcp:send(Socket,Str),
            case gen_tcp:recv(Socket,0) of
                {ok, Paquete} -> io:format("Recibi el echo ~p ~n",[Paquete]);
                {error, Reason} -> io:format("Error: ~p ~n",[Reason])
            end,
            gen_tcp:close(Socket),
            ok;
        {error, Reason} -> io:format("Error: ~p ~n",[Reason])
        end.
