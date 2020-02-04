let helpText = {js|INSTRUCTIONS:

Playing this game is fairly straightforward! Simply click on the highlighted keywords to advance the story in the indicated way. There may be other ways to progress, if you keep an eye out.

Ⓒ 2020 Andrea Zonghao Chen|js};

[@react.component]
let make = (~onClose: unit => unit) =>
  <Dialog onClose>
    {React.string(helpText)}
  </Dialog>