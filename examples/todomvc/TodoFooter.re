let component = ReasonReact.statelessComponent("TodoFooter");

let make =
    (
      ~count,
      ~completedCount,
      ~nowShowing,
      ~onClearCompleted,
      ~onViewClick,
      _children,
    ) => {
  ...component,
  render: _self => {
    let activeTodoWord = Z.to_int(count) == 1 ? "item" : "items";
    let clearButton =
      Z.to_int(completedCount) > 0 ?
        <button className="clear-completed" onClick=(_e => onClearCompleted())>
          (ReasonReact.string("Clear completed"))
        </button> :
        ReasonReact.null;
    let (all, active, completed) =
      switch ((nowShowing: TodoMvcModel.view)) {
      | AllTodos => ("selected", "", "")
      | ActiveTodos => ("", "selected", "")
      | CompletedTodos => ("", "", "selected")
      };
    <footer className="footer">
      <span className="todo-count">
        <strong> (ReasonReact.string(Z.to_string(count))) </strong>
        (ReasonReact.string(" " ++ activeTodoWord ++ " left"))
      </span>
      <ul className="filters">
        <li>
          <a
            onClick=(
              e => {
                onViewClick(TodoMvcModel.AllTodos);
                ReactEvent.Mouse.preventDefault(e);
              }
            )
            className=all>
            (ReasonReact.string("All"))
          </a>
        </li>
        (ReasonReact.string(" "))
        <li>
          <a
            onClick=(
              e => {
                onViewClick(TodoMvcModel.ActiveTodos);
                ReactEvent.Mouse.preventDefault(e);
              }
            )
            className=active>
            (ReasonReact.string("Active"))
          </a>
        </li>
        (ReasonReact.string(" "))
        <li>
          <a
            onClick=(
              e => {
                onViewClick(TodoMvcModel.CompletedTodos);
                ReactEvent.Mouse.preventDefault(e);
              }
            )
            className=completed>
            (ReasonReact.string("Completed"))
          </a>
        </li>
      </ul>
      clearButton
    </footer>;
  },
};