open Jest;

module I = Imandra_client;

let serverInfo = ref(None);

let moduleName = "TodoMvc_Model";

let () =
  beforeAllPromise(() => {
    let si = Imandra_client.Server_info.from_file() |> Belt.Result.getExn;
    serverInfo := Some(si);
    Js.Promise.resolve();
  });

let syntax = I.Api.Reason;

describe("todomvc model", () => {
  beforeAllPromise(() => {
    let ip = serverInfo^ |> Belt.Option.getExn;
    let model_path =
      Node.Path.join([|
        [%raw "__dirname"],
        "..",
        Printf.sprintf("%s.ire", moduleName),
      |]);
    Imandra_client.Eval.by_src(
      ip,
      ~syntax,
      ~src=Printf.sprintf("#mod_use \"%s\"", model_path),
    )
    |> Js.Promise.then_(
         fun
         | Belt.Result.Ok(_) => Js.Promise.resolve(pass)
         | Belt.Result.Error(e) => {
             Js.Console.error(I.Error.pp_str(e));
             Js.Promise.reject(Failure(I.Error.pp_str(e)));
           },
       );
  });

  afterAllPromise(() =>
    Js.Promise.make((~resolve, ~reject) =>
      Js.Global.setTimeout(
        () =>
          Imandra_client.reset(serverInfo^ |> Belt.Option.getExn)
          |> Js.Promise.then_(
               fun
               | Belt.Result.Ok(_) => {
                   resolve(. pass);
                   Js.Promise.resolve();
                 }
               | Belt.Result.Error(e) => {
                   Js.Console.error(I.Error.pp_str(e));
                   reject(. Failure(I.Error.pp_str(e)));
                   Js.Promise.resolve();
                 },
             )
          |> ignore,
        500,
      )
      |> ignore
    )
  );

  testPromise("vg_add_todo", () => {
    let ip = serverInfo^ |> Belt.Option.getExn;
    let functionName =
      Imandra_client.function_name(TodoMvc_Model.vg_add_todo);
    let name = Printf.sprintf("%s.%s", moduleName, functionName);
    let hints = I.Api.Request.Hints.{method_: Induct(Default)};
    Imandra_client.Verify.by_name(ip, ~name, ~hints)
    |> Js.Promise.then_(res =>
         Js.Promise.resolve(Imandra_client_expect.to_be_proved(res))
       );
  });
  testPromise("vg_clear_completed", () => {
    let ip = serverInfo^ |> Belt.Option.getExn;
    let functionName =
      Imandra_client.function_name(TodoMvc_Model.vg_clear_completed);
    let name = Printf.sprintf("%s.%s", moduleName, functionName);
    let hints = I.Api.Request.Hints.{method_: Induct(Default)};
    Imandra_client.Verify.by_name(ip, ~name, ~hints)
    |> Js.Promise.then_(res =>
         Js.Promise.resolve(Imandra_client_expect.to_be_proved(res))
       );
  });
  testPromise("vg_toggle_all", () => {
    let ip = serverInfo^ |> Belt.Option.getExn;
    let functionName =
      Imandra_client.function_name(TodoMvc_Model.vg_toggle_all);
    let name = Printf.sprintf("%s.%s", moduleName, functionName);
    let hints = I.Api.Request.Hints.{method_: Induct(Default)};
    Imandra_client.Verify.by_name(ip, ~name, ~hints)
    |> Js.Promise.then_(res =>
         Js.Promise.resolve(Imandra_client_expect.to_be_proved(res))
       );
  });
  testPromise("vg_edit_todo", () => {
    let ip = serverInfo^ |> Belt.Option.getExn;
    let functionName =
      Imandra_client.function_name(TodoMvc_Model.vg_edit_todo);
    let name = Printf.sprintf("%s.%s", moduleName, functionName);
    let hints = I.Api.Request.Hints.{method_: Induct(Default)};
    Imandra_client.Verify.by_name(ip, ~name, ~hints)
    |> Js.Promise.then_(res =>
         Js.Promise.resolve(Imandra_client_expect.to_be_proved(res))
       );
  });
});
