module Styles = {
  open Css;

  let text = style([
    whiteSpace(`preWrap),
  ]);
}

[@react.component]
let make = (~children: string) =>
  <span className=Styles.text>{React.string(children)}</span>;