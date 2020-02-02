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

  let textBlock = style([marginBottom(`px(20))]);
};

[@react.component]
let make = () => {
  let (globalState, _globalDispatch) = GlobalState.useGlobalState();

  <div className=Styles.scrollContainer>
    {globalState.narrationHistory
     ->Belt.List.mapWithIndex((index, narration) =>
         <div className=Styles.textBlock key={string_of_int(index)}>
           {React.string(narration)}
         </div>
       )
     ->Belt.List.toArray
     ->React.array}
  </div>;
};