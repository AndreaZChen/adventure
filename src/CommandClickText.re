[@react.component]
let make = (~command: Command.t, ~text: string) => {
  let (_, globalDispatch) = GlobalState.useGlobalState();

  let onClick =
    React.useCallback2(
      _ => globalDispatch(CommandTextClicked(command)),
      (command, globalDispatch),
    );

  <a href="#" role="button" onClick> {React.string(text)} </a>;
};