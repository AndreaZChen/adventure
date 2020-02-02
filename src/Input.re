module Styles = {
  open Css;

  let wrapper =
    style([display(`flex), width(`percent(100.)), alignItems(`center)]);

  let inputField = style([flexGrow(1.)]);

  let angleBracketSpan = style([whiteSpace(`pre)]);
};

let enterKeyCode = 13;

[@react.component]
let make = () => {
  let (globalState, globalDispatch) = GlobalState.useGlobalState();

  let onKeyDown =
    React.useCallback1(
      event =>
        ReactEvent.Keyboard.keyCode(event) == enterKeyCode
          ? globalDispatch(GlobalState.ActionSent) : (),
      [|globalDispatch|],
    );

  let onChange =
    React.useCallback1(
      event =>
        ReactEvent.Form.target(event)##value
        ->GlobalState.ActionInputFieldUpdated
        ->globalDispatch,
      [|globalDispatch|],
    );

  <div className=Styles.wrapper>
    <div>
      <span className=Styles.angleBracketSpan> {React.string("> ")} </span>
    </div>
    <input
      className=Styles.inputField
      value={globalState.currentActionInputFieldValue}
      type_="text"
      onKeyDown
      onChange
    />
  </div>;
};