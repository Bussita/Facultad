-module(balanceo).
-export([init/0, bal/1,server/0]).

bal(Servs) ->
    receive
        {req, Arg, Pid} ->
            ServElegido = lists:nth(rand:uniform(length(Servs)), Servs),
            ServElegido ! {req, Arg, self()},
            receive
                {ServElegido, Reply, Argumento} -> Pid ! {Reply,Argumento}
            end
    end,
    bal(Servs).



server() ->
        receive
            {req,Arg, Pid} -> 
                Pid ! {self(),"Se ha operado el argumento",Arg+1},
                server()
        end.

init() ->
    P1 = spawn(balanceo, server, []),
    P2 = spawn(balanceo, server, []),
    P3 = spawn(balanceo, server, []),
    P4 = spawn(balanceo, server, []),
    P5 = spawn(balanceo, server, []),
    P6 = spawn(balanceo, server, []),
    Servidores = [P1, P2, P3, P4, P5, P6],
    bal(Servidores).
