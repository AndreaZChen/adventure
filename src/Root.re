module Styles = {
  open Css;

  let rootWrapper = (~backgroundColorHex) =>
    style([
      overflow(`hidden),
      position(`absolute),
      display(`flex),
      alignItems(`center),
      justifyContent(`center),
      flexDirection(`column),
      width(`percent(100.)),
      height(`percent(100.)),
      bottom(`px(0)),
      right(`px(0)),
      transitionDuration(500),
      background(
        `linearGradient((
          `deg(90.),
          [
            (`percent(0.), `hex(backgroundColorHex)),
            (`percent(5.), `hex(CommonStyles.defaultBackgroundHex)),
            (`percent(95.), `hex(CommonStyles.defaultBackgroundHex)),
            (`percent(100.), `hex(backgroundColorHex)),
          ],
        )),
      ),
    ]);

  let title = style([padding(`px(15))]);

  let centralColumn =
    style([
      overflowX(`hidden),
      overflowY(`auto),
      position(`relative),
      display(`flex),
      flexDirection(`column),
      width(`percent(80.)),
      height(`percent(80.)),
    ]);

  global(
    "body",
    [
      fontFamily("Lato"),
      lineHeight(`abs(1.8)),
      backgroundColor(`hex(CommonStyles.defaultBackgroundHex)),
    ],
  );
};

let getInitialState: unit => GlobalState.t =
  () =>
    GlobalState.loadState()
    ->Belt.Option.getWithDefault({
        ...GlobalState.defaultState,
        currentSceneId: InitialScene.Scene.id,
      });

[@react.component]
let make = () => {
  let (globalState, globalDispatch) =
    ReactUpdate.useReducer(getInitialState(), GlobalState.reducer);

  let centralColumnRef = React.useRef(Js.Nullable.null);

  let scrollToTop =
    React.useCallback1(
      () =>
        centralColumnRef
        ->React.Ref.current
        ->Js.Nullable.toOption
        ->Belt.Option.mapWithDefault((), element =>
            Webapi.Dom.Element.setScrollTop(element, 0.)
          ),
      [|centralColumnRef|],
    );

  let onCloseHelpDialog =
    React.useCallback1(
      () => globalDispatch(HelpDialogClosed),
      [|globalDispatch|],
    );

  let onCloseCharacterMenu =
    React.useCallback1(
      () => globalDispatch(CharacterMenuClosed),
      [|globalDispatch|],
    );

  let (module CurrentScene): (module Interfaces.Scene) =
    React.useMemo1(
      () => SceneUtils.getSceneById(globalState.currentSceneId),
      [|globalState.currentSceneId|],
    );

  <div
    className={Styles.rootWrapper(
      ~backgroundColorHex=CurrentScene.backgroundColorHex,
    )}>
    <HelpButton globalDispatch />
    <CharacterMenuButton globalDispatch />
    <ScrollToTopProvider value=scrollToTop>
      <h3 className=Styles.title> {React.string(CurrentScene.title)} </h3>
      <div
        className=Styles.centralColumn
        ref={ReactDOMRe.Ref.domRef(centralColumnRef)}>
        {CurrentScene.renderer(~globalState, ~globalDispatch)}
      </div>
    </ScrollToTopProvider>
    {globalState.isShowingHelpDialog
       ? <HelpDialog onClose=onCloseHelpDialog />
       : globalState.isShowingCharacterMenu
           ? <CharacterMenu globalState onClose=onCloseCharacterMenu />
           : React.null}
  </div>;
};