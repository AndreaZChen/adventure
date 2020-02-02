module Styles = {
  open Css;

  let scrollContainer =
    style([
      overflow(`auto),
      display(`flex),
      flexDirection(`columnReverse),
      alignItems(`flexStart),
      width(`percent(100.)),
      height(`percent(100.)),
    ]);

  let narrationItem = style([whiteSpace(`preWrap), marginBottom(`px(20))]);
};

[@react.component]
let make = () => {
  let (globalState, _) = GlobalState.useGlobalState();

  <div className=Styles.scrollContainer>
    {globalState.narrationHistory
     ->Belt.List.mapWithIndex((index, narration) => {
         let key =
           string_of_int(
             Belt.List.length(globalState.narrationHistory) - index,
           );
         <div className=Styles.narrationItem key> narration </div>;
       })
     ->Belt.List.toArray
     ->React.array}
  </div>;
};