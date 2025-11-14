-module(pingPong).
-export([pong/0, ping/0,play/0]).

pong() ->
    receive
        {0, PidPing} ->
            io:fwrite("final pong! ~n"),
            PidPing ! {fin, self()},
            pongok;
        {N, PidPing} ->
            io:fwrite("pong! recv: ~p ~n",[N]),
            PidPing!{(N-1), self()},
            pong()
    end.

ping() -> 
    receive
        {fin, _} ->
            io:fwrite("final ping! ~n"),
            pingok;
        {N, PidPong} ->
            io:fwrite("Ping!"),
            PidPong ! {N, self()},
            ping()
    end.

play() ->
    PidPong = spawn(pingPong, pong , []),
    PidPing = spawn(pingPong, ping, []),
    PidPong ! {10,PidPing},
    playok.