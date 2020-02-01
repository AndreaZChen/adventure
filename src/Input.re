let enterKeyCode = 13;

[@react.component]
let make = () => {
  let (_globalState, globalDispatch) = GlobalState.useGlobalState();

  let onKeyDown =
    React.useCallback1(
      event =>
        ReactEvent.Keyboard.keyCode(event) == enterKeyCode
          ? ReactEvent.Keyboard.target(event)##value
            ->GlobalState.InputAction
            ->globalDispatch
          : (),
      [|globalDispatch|],
    );

  <input type_="text" onKeyDown />;
};