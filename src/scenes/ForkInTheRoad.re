type action =
  | NextScene;

let actionHandler = (~globalDispatch: GlobalState.action => unit, action: action) =>
  switch (action) {
  | NextScene =>
    globalDispatch(SceneTransitioned((~globalState, ~globalDispatch) => React.null))
  };

module Component = {
  let narration =
{|A fork in the road...|};

  [@react.component]
  let make = (~globalDispatch: GlobalState.action => unit) => {
    let actionHandler = React.useCallback1(actionHandler(~globalDispatch), [|globalDispatch|]);

    <>
      <FadeInElement fadeInTime=3000>
        {React.string(narration)}
      </FadeInElement>
      <FadeInElement fadeInTime=6000 startFadeInAtPercent=50>
        <ClickableText onClick={() => actionHandler(NextScene)} text="help" />
      </FadeInElement>
    </>;
  };
};

let renderer: GlobalState.sceneRenderer = (~globalState as _, ~globalDispatch) =>
  <Component globalDispatch />;