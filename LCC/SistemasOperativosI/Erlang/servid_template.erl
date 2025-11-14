-module(servid_template).
%%%%%%
%% Pequeño ejercicio de clase
%% el servidor aceptara 4 tipos de pedidos/mensajes:
%% + nuevoId(Nombre, PidResp) -> Se generará un nuevo identificar para `Nombre` y se responderá al cliente.
%% + buscarId(Id, PidResp) -> Se responde a `PidResp` el nombre asociado a `Id`.
%% + verLista(PidResp) -> Se envía a `Pidresp` la lista de pares (Id,Nombre).
%% + finalizar(PidResp) -> Se finaliza el servicio y se responde con un `ok`.
%%
-include("servid_template.hrl").
%% Creación y eliminación del servicio
-export([iniciar/0, finalizar/0]).


%% Librería de Acceso
-export([nuevoNombre/1, quienEs/1, listaDeIds/0]).

%% Funciones de testing
-export([test/0,client/0]).

%% Servidor
-export([serverinit/0, servnombres/2]).
% Iniciar crea el proceso servidor, y devuelve el PId.
iniciar() ->
  Pid = spawn(?MODULE, serverinit, []),
  register(servidor, Pid).

%%%%%%%%%%%%%% Librería de Acceso
%% Dado un nombre y un servidor le pide que cree un identificador único.
nuevoNombre(Nombre) ->
  servidor ! #nuevoId{nombre = Nombre, cid =self()},
  receive
    {ok, Id} -> io:format("Se asocio el nombre ~p al id ~p ~n",[Nombre,Id]);
    _ -> error
  end.

%% Función que recupera el nombre desde un Id
quienEs(Id) ->
  servidor ! {buscarId, Id, self()},
  receive
    {ok, Nombre} -> io:format("El nombre asociado al id ~p es ~p ~n",[Id,Nombre]);
    _ -> error
  end.

%% Pedimos la lista completa de nombres e identificadores.
listaDeIds() ->
  servidor ! {verLista, self()},
  receive
    {ok, Lista} -> io:format("La lista completa es ~p~n",[Lista]);
    _ -> error
  end.

% Ya implementada :D!
finalizar() ->
  servidor ! {finalizar, self()}.

%%%%%%%%%%% Servidor
%% Función de servidor de nombres.
serverinit() ->
    %% Comenzamos con un mapa nuevo, y un contador en 0.
    servnombres(maps:new(),0).


servnombres(Map, N) ->
    receive
        %% Llega una petición para crear un Id para nombre
        #nuevoId{nombre = Nombre, cid = CId} ->
            CId ! {ok, N},
            servnombres(maps:put(N, Nombre, Map),N+1);
        %% Llega una petición para saber el nombre de tal Id
        {buscarId, NId, CId} -> 
            Nombre = maps:find(NId, Map),
            CId ! {ok, Nombre},
            servnombres(Map,N);
                              
        %% Entrega la lista completa de Ids con Nombres.
        {verLista, CId} -> 
            CId ! {ok, maps:to_list(Map)},
            servnombres(Map, N);
        %% Cerramos el servidor.
        {finalizar, CId } -> 
          io:format("Servidor cerrado por el cliente ~p~n",[CId]),
          fin;
        _ -> 
          io:format("DBG: Mensaje incorrecto.~n"),
          servnombres(Map, N)
    end.

client() ->
  nuevoNombre(pepa),
  listaDeIds(),
  nuevoNombre(pepe),
  listaDeIds(),
  quienEs(0),
  quienEs(1),
  finalizar(),
  ok.

test() ->
  servid_template:iniciar(),
  spawn(?MODULE, client, []),
  ok.
