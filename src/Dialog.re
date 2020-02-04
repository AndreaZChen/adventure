module Styles = {
  open Css;

  let overlay = style([
    zIndex(CommonStyles.dialogZIndex),
    width(`percent(100.)),
    height(`percent(100.)),
    position(`absolute),
    top(`px(0)),
    left(`px(0)),
  ]);

  let transparentBackground = style([
    zIndex(CommonStyles.dialogZIndex),
    width(`percent(100.)),
    height(`percent(100.)),
    position(`absolute),
    top(`px(0)),
    left(`px(0)),
    background(`rgba(0, 0, 0, 0.5)),
    display(`flex),
    alignItems(`center),
    justifyContent(`center),
  ]);

  let content = style([
    zIndex(CommonStyles.dialogZIndex + 1),
    maxWidth(`percent(80.)),
    maxHeight(`percent(80.)),
    backgroundColor(`hex(CommonStyles.defaultBackgroundHex)),
    border(`px(1), solid, `hex(CommonStyles.defaultBorderHex)),
    padding(`px(25)),
    whiteSpace(`preWrap),
  ]);
}

[@react.component]
let make = (~onClose: unit => unit, ~children) => {
  let onClose = React.useCallback1(_ => onClose(), [|onClose|]);

  <div className=Styles.overlay onClick=onClose>
    <FadeInElement fadeInTime=250>
      <div className=Styles.transparentBackground>
        <div className=Styles.content>
            children
        </div>
      </div>
    </FadeInElement>
  </div>;
}