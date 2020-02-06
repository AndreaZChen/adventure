type state = {
  timesSpokenStielettaAnethir: int,
  timesSpokenAnethirJaziel: int,
  timesSpokenJazielStieletta: int,
};

let initialState = {
  timesSpokenStielettaAnethir: 0,
  timesSpokenAnethirJaziel: 0,
  timesSpokenJazielStieletta: 0,
};

type action =
  | GoNorth
  | GoEast
  | GoWest
  | SpeakStielettaAnethir
  | SpeakAnethirJaziel
  | SpeakJazielStieletta;

let actionHandler = (~globalDispatch: GlobalState.action => unit, ~localDispatch, action: action) =>
  switch (action) {
  | GoNorth =>
    ();
  | GoEast =>
    ();
  | GoWest =>
    ();
  | SpeakStielettaAnethir =>
    ();
  | SpeakAnethirJaziel =>
    ();
  | SpeakJazielStieletta =>
    ();
  };

module Component = {
  [@react.component]
  let make = (~globalDispatch: GlobalState.action => unit) => {
    let (localState, localDispatch) = React.useState(() => initialState);

    let actionHandler = React.useCallback2(actionHandler(~globalDispatch, ~localDispatch), (globalDispatch, localDispatch));
    <>
      <FadeInDiv fadeInTime=6000>
        <Text>"[To be continued...]"</Text>
      </FadeInDiv>
      // <FadeInDiv className=CommonStyles.buttonsArea fadeInTime=12000 startFadeInAt=9000>
      //   <button onClick={_ => actionHandler(GoNorth)}>
      //     {React.string("Go North")}
      //   </button>
      //   <button onClick={_ => actionHandler(GoEast)}>
      //     {React.string("Go East")}
      //   </button>
      //   <button onClick={_ => actionHandler(GoWest)}>
      //     {React.string("Go West")}
      //   </button>
      // </FadeInDiv>
    </>;
  };
};

let renderer: GlobalState.sceneRenderer = (~globalState as _, ~globalDispatch) =>
  <Component globalDispatch />;