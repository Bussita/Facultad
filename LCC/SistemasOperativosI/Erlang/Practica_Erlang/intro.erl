-module(intro).
-export([init/0,string_test/0,tuple_test/2]).

match_test() ->
    {A, B} = {5, 4},
    {C, C} = {5, 4},
    {B, A} = {4, 5},
    {D, D} = {5, 5}.

string_test () -> [
    helloworld == 'helloworld', % true: esto ocurre ya que hello world es un atomo y las comillas simples no hacen nada
    "helloworld" < 'helloworld', % false: orden total de tipos
    helloworld == "helloworld", % false: orden total de tipos 
    [$h,$e,$l,$l,$o,$w,$o,$r,$l,$d] == "helloworld", % true: $ para caracter
    [104,101,108,108,111,119,111,114,108,100] < {104,101,108,108,111,119,111,114,108,100}, % false: orden total de tipos
    [104,101,108,108,111,119,111,114,108,100] > 1, % true: orden total de tipos
    [104,101,108,108,111,119,111,114,108,100] == "helloworld"]. % true: los strings se codifican en cadenas de números, que son los del ascii

    % Erlang tiene implementado un orden total de tipos: number < atom < reference < fun < port < pid < tuple < map < nil < list < bitstring
tuple_test(P1, P2) ->
    io:fwrite("El nombre de P1 es ~p y el apellido de P2 es ~p~n", [nombre(P1), apellido(P2)]).

apellido(P) -> case P of
            {_,_,{apellido, []}} -> vacio;
            {_,_,{apellido, StringApellido}} -> StringApellido
        end.

nombre(P) -> case P of
            {_,{nombre, []},_} -> vacio;
            {_,{nombre, StringNombre},_} -> StringNombre
        end.

filtrar_por_apellido(Personas, Apellido) -> case Personas of
                                        [] -> [];                                 
                                        [{_,{nombre,StringNombre},{apellido,Apellido}} | Ps] -> [{StringNombre, Apellido} | filtrar_por_apellido(Ps,Apellido)];
                                        [_|Ps] -> filtrar_por_apellido(Ps, Apellido)
                                    end.

init() ->
    P1 = {persona, {nombre, "Juan"}, {apellido, "Gomez"}},
    P2 = {persona, {nombre, "Carlos"}, {apellido, "Garcia"}},
    P3 = {persona, {nombre, "Javier"}, {apellido, "Garcia"}},
    P4 = {persona, {nombre, "Rolando"}, {apellido, "Garcia"}},
    %match_test(),
    tuple_test(P1, P2),
    string_test(),
    Garcias = filtrar_por_apellido([P4, P3, P2, P1], "Garcia"),
    io:fwrite("La lista de personas con apellido Garcia es ~p~n", [Garcias]).
