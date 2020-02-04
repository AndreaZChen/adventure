type action =
  | NextScene;

let actionHandler = (~globalDispatch: GlobalState.action => unit, action: action) =>
  switch (action) {
  | NextScene =>
    globalDispatch(SceneTransitioned(ForkInTheRoad.renderer))
  };

module Component = {
  let narration =
{|Three friends are seated around a campfire.

It is nearly nighttime. There's not much to do but go to bed, and yet... none of the three feel eager to sleep.

What will they do now?|};

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