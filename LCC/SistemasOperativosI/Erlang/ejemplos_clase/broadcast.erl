-module(broadcast).
-export([iniciar/0,finalizar/0]).
-export([bdcast/1,registrar/0]).
-export([loopbroadcast/1]).

%% Podemos utilizar la función list:foreach(fun(Pid) -> Pid ! Msg end, PidList).

%% registrar dado un pid lo registra en la lista de clientes.
%% broadcast(Msg) manda un broadcast a todos los clientes
registrar() -> 
    serv ! {registrarme, self()}.

iniciar() ->
    register(serv, spawn(broadcast, loopbroadcast, [[]])).

finalizar() ->
    serv ! fin.
loopbroadcast(ListaClientes) ->
    receive
        {mandarMensaje, Msg} ->
            bdcast(Msg),
            loopbroadcast(ListaClientes);
        {registrarme, PidCliente} -> 
            loopbroadcast([PidCliente | ListaClientes]);
        fin -> ok
    end.

bdcast(Msg) ->
    serv ! {mandarMensaje, Msg}.
