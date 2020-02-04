type action =
  | NextScene;

let actionHandler = (~globalDispatch: GlobalState.action => unit, action: action) =>
  switch (action) {
  | NextScene =>
    globalDispatch(SceneTransitioned(ForkInTheRoad.renderer))
  };

module Component = {
  let narration1 =
"Three friends walk down a well-trod path in the woods.

It is springtime; the forest is verdant and replete with life. The pine trees are tall and cast long, dark shadows across the earth; \
birdsong resounds between their crowns. Rays of sunlight trickle between holes in the canopy, and the alternating speckles of sun and shadow \
lend an overall pleasant atmosphere to the forest.";

  let narration2 =
"Our friends are Stieletta, Anethir, and Jaziel. You already know them, of course. \
But you don't know where this particular chapter of their story will take them.

Let's find out together, shall we?";

  [@react.component]
  let make = (~globalDispatch: GlobalState.action => unit) => {
    let actionHandler = React.useCallback1(actionHandler(~globalDispatch), [|globalDispatch|]);

    <>
      <FadeInDiv fadeInTime=6000>
        <Text>narration1</Text>
      </FadeInDiv>
      <br />
      <FadeInDiv fadeInTime=9000 startFadeInAt=6000>
        <Text>narration2</Text>
      </FadeInDiv>
      <br />
      <FadeInDiv fadeInTime=12000 startFadeInAt=9000>
        <button onClick={_ => actionHandler(NextScene)}>
          {React.string("Next")}
        </button>
      </FadeInDiv>
    </>;
  };
};

let renderer: GlobalState.sceneRenderer = (~globalState as _, ~globalDispatch) =>
  <Component globalDispatch />;